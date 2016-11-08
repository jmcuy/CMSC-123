import java.io.*;
import java.util.ArrayList;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

public class TeeOfEn {
	private static final String DELIMITER1 = "\\s*;\\s*";
	private static final String DELIMITER2 = "\\s*;+\\s*";
	private static final String DELIMITER3 = "\\s*,\\s*";

	//Tokens of the initialization, condition, changer, and operations
	private ArrayList<String> init = new ArrayList<String>(0);
	private ArrayList<String> condit = new ArrayList<String>(0);
	private ArrayList<String> changer = new ArrayList<String>(0);
	private ArrayList<String> operations = new ArrayList<String>(0); 

	//Significant operations in the for loop
	private String signifInit;
	private String signifCondit;
	private String signifChanger;

	//Values and operators of the significant operations in the for loop
	private String initVal;
	private String conditVal;
	private String changerVal;
	private String conditOp;
	private String changerOp;

	//Parts of the T of En
	private int type;  //1, 2, 3 ,4
	private String coefficient;
	private String residual;

	/*****************Initialization*******************/
	TeeOfEn(String inputFile) throws IOException {
		FileInputStream fInStream = new FileInputStream(inputFile);
		BufferedReader br = new BufferedReader(new InputStreamReader(fInStream));
		
		String strLine;
		while ((strLine = br.readLine()) != null)   {
  			tokenize(strLine);
		}

		initializeSignif();
		initializeValOp();
		initializeParts();
		
		br.close();
	}

	private void tokenize(String s) {
		if(s.contains("for")) {
			String[] tokens = truncUnnecessary(s).split(DELIMITER1);
			tokenizeSubtokens(tokens);
		} else if(!s.contains("}")) {
			String[] tokens = truncPreSpaces(s).split(DELIMITER2);
			saveToOperations(tokens);	
		}
	}

	private static String truncUnnecessary(String s) {
		int firstParen = -1;
		int secondParen = -1;
		for(int i = 0; i < s.length(); i++) {
			if(s.charAt(i) == '(') {
				firstParen = i;
				break;
			}
		}

		for(int i = s.length() - 1; i >= 0; i--) {
			if(s.charAt(i) == ')') {
				secondParen = i;
				break;
			}
		}

		return s.substring(firstParen+1, secondParen);
	}

	private static String truncPreSpaces(String s) {
		int index = -1;
		for(int i = 0; i < s.length(); i++) {
			if(s.charAt(i) != ' ') {
				index = i;
				break;
			}
		}

		return s.substring(index);
	}	

	private void tokenizeSubtokens(String[] tokens) {
		for(int i = 0; i < tokens.length; i++) {
			String[] subTokens = tokens[i].split(DELIMITER3);
			switch(i) {
				case 0: saveToInit(subTokens);
						break;
				case 1: saveToCondit(subTokens);
						break;
				case 2: saveToChange(subTokens);
						break;
			}
		}
	}

	private void saveToInit(String[] subTokens) {
		for(int i = 0; i < subTokens.length; i++) {
			init.add(subTokens[i]);
		}
	}

	private void saveToCondit(String[] subTokens) {
		for(int i = 0; i < subTokens.length; i++) {
			condit.add(subTokens[i]);
		}
	}	

	private void saveToChange(String[] subTokens) {
		for(int i = 0; i < subTokens.length; i++) {
			changer.add(subTokens[i]);
		}
	}

	private void saveToOperations(String[] subTokens) {
		for(int i = 0; i < subTokens.length; i++) {
			operations.add(subTokens[i]);
		}
	}

	private void initializeSignif() {
		// For this sample, the significant init, condit, 
		// and changer is the first of each. This assumes that 
		// there is only one init, condit, and changer
		signifInit = init.get(0);
		signifCondit = condit.get(0);
		signifChanger = changer.get(0);
	}

	private void initializeValOp() {
		initVal = detInitVal();
		conditVal = detConditVal();
		changerVal = detChangerVal();
		conditOp = detConditOp();
		changerOp = detChangerOp();
	}

	private String detInitVal() {
        Pattern pattern = Pattern.compile("=\\s*");
        Matcher matcher = pattern.matcher(signifInit);

        matcher.find();
        return signifInit.substring(matcher.end());
	}

	private String detConditVal() {
        Pattern pattern = Pattern.compile("[<>=][=]?\\s*");
        Matcher matcher = pattern.matcher(signifCondit);

        matcher.find();
        return signifCondit.substring(matcher.end());
	}

	private String detChangerVal() {
		if(signifChanger.contains("++") || signifChanger.contains("--")) {
			return "1";
		} else {
        	Pattern pattern = Pattern.compile("[+*-/][=]\\s*");
        	Matcher matcher = pattern.matcher(signifChanger);

	        matcher.find();
        	return signifChanger.substring(matcher.end());
		}
	}

	private String detConditOp() {
		Pattern pattern = Pattern.compile("[<>=][=]?");
        Matcher matcher = pattern.matcher(signifCondit);

        matcher.find();
        return signifCondit.substring(matcher.start(), matcher.end());
	}
	private String detChangerOp() {
		if(signifChanger.contains("++")) {
			return "+=";
		} else if(signifChanger.contains("--")) {
			return "-=";
		} else {
        	Pattern pattern = Pattern.compile("[+*-/][=]");
        	Matcher matcher = pattern.matcher(signifChanger);

	        matcher.find();
        	return signifChanger.substring(matcher.start(), matcher.end());
		}
	}

	private void initializeParts() {
		type = detType();
		coefficient = detCoefficient();
		residual = detResidual();
	}

	private int detType() {
		if(!isInfinite()) {
			if(!isPowered()) {
				if(changerOp.equals("+=") || changerOp.equals("-=")) {
					return 1;
				} else {
					return 2;
				}
			} else {
				return 4;
			}
		} else {
			return 3;
		}
	}

	private String detCoefficient() {
		int coeff = 0;

		//condition
		for(int i = 0; i < condit.size(); i++) {
			coeff += unitTimeCounter(condit.get(i));
		}
		//changer
		for(int i = 0; i < changer.size(); i++) {
			coeff += unitTimeCounter(changer.get(i));
		}
		//operations
		for(int i = 0; i < operations.size(); i++) {
			coeff += unitTimeCounter(operations.get(i));
		}

		return String.valueOf(coeff);
	}

	private String detResidual() {
		int resid = 0;

		//initialization
		for(int i = 0; i < init.size(); i++) {
			resid += unitTimeCounter(init.get(i));
		}
		//condition
		for(int i = 0; i < init.size(); i++) {
			resid += unitTimeCounter(condit.get(i));
		}

		return String.valueOf(resid);
	}

	/************************************************/

	/******************Show Tokens*******************/
	public void showInit() {
		for(int i = 0; i < init.size(); i++) {
			System.out.println(init.get(i));
		}
	}

	public void showCondit() {
		for(int i = 0; i < condit.size(); i++) {
			System.out.println(condit.get(i));
		}
	}

	public void showChanger() {
		for(int i = 0; i < changer.size(); i++) {
			System.out.println(changer.get(i));
		}
	}

	public void showOperations() {
		for(int i = 0; i < operations.size(); i++) {
			System.out.println(operations.get(i));
		}
	}

	public void showAllTokens() {
		System.out.println("Initializations: ");
		showInit();
		System.out.println();

		System.out.println("Conditions: ");
		showCondit();
		System.out.println();

		System.out.println("Changer: ");
		showChanger();
		System.out.println();

		System.out.println("Operations: ");
		showOperations();
	}
	/************************************************/

	/******************Show Parts********************/
	public int getType() {
		return type;
	}

	public String getCoefficient() {
		return coefficient;
	}

	public String getResidual() {
		return residual;
	}

	public void showAllParts() {
		System.out.println("Type: " + type);
		System.out.println("Coefficient: " + coefficient);
		System.out.println("Residual: " + residual);
	}

	/************************************************/	
	
	public String answer() {
		switch(type) {
			case 1: 
				return solveType1();
			case 2: 
				return solveType2();
			case 3: 
				return solveType3();
			case 4: 
				return solveType4();
		}
		return "";
	}

	/*
	*	Type 1 Solution
	*/
	private String solveType1() {
		String coefficient = getCoefficient();
		String residual = getResidual();

		int coefficientInt = Integer.valueOf(coefficient);
		int residualInt = Integer.valueOf(residual);
		if(changerOp.equals("+=")) {
			if(!initVal.matches("\\d+") || !conditVal.matches("\\d+")) {
				String upperBound = "ceil((" + conditVal + " - " + initVal + ") / " + changerVal + ")";
				return "T(n)= (" + coefficient + " * " + upperBound + ") + " + residual + 
					   "\n      or\n      " +
					   "(" + coefficient + " * " + "(" + upperBound + " + 1)) + " + residual +
					   " if " + conditVal + " + " + changerVal + " = " + initVal + " (mod " + 
					   changerVal + ")";
			} else {
				int upperBoundInt = (int) (Math.ceil((Integer.valueOf(conditVal) - 
							Integer.valueOf(initVal)) / Integer.valueOf(changerVal)) + 
							plusOneType1());
				return "T(n)= " + String.valueOf((coefficientInt * upperBoundInt) + residualInt);
			}
		} else { //inverted type
			if(!initVal.matches("\\d+") || !conditVal.matches("\\d+")) {
				String upperBound = "ceil((" + initVal + " - " + conditVal + ") / " + changerVal + ")";
				return "T(n)= (" + coefficient + " * " + upperBound + ") + " + residual + 
					   "\n      or\n      " +
					   "(" + coefficient + " * " + "(" + upperBound + " + 1)) + " + residual +
					   " if " + initVal + " + " + changerVal + " = " + conditVal + " (mod " + 
					   changerVal + ")";
			} else {
				int upperBoundInt = (int) (Math.ceil((Integer.valueOf(initVal) - 
							Integer.valueOf(conditVal)) / Integer.valueOf(changerVal)) + 
							plusOneType1Inv());
				return "T(n)= " + String.valueOf((coefficientInt * upperBoundInt) + residualInt);
			}
		}
	}

	private int plusOneType1() {
		int initValInt = Integer.valueOf(initVal);
		int conditValInt = Integer.valueOf(conditVal);
		int changerValInt = Integer.valueOf(changerVal);
		while(conditValInt >= initValInt) {
			if(conditValInt == initValInt) {
				return 1;
			}
			conditValInt -= changerValInt;
		}
		return 0;
	}

	private int plusOneType1Inv() {
		int initValInt = Integer.valueOf(initVal);
		int conditValInt = Integer.valueOf(conditVal);
		int changerValInt = Integer.valueOf(changerVal);
		while(initValInt >= conditValInt) {
			if(initValInt == conditValInt) {
				return 1;
			}
			initValInt -= changerValInt;
		}
		return 0;
	}

	/*
	*	Type 2 Solution
	*/
	private String solveType2() {
		String coefficent = getCoefficient();
		String residual = getResidual();

		int coefficientInt = Integer.valueOf(coefficient);
		int residualInt = Integer.valueOf(residual);

		if(changerOp.equals("*=")) {
			if(!initVal.matches("\\d+") || !conditVal.matches("\\d+")) {
				String upperBound = "ceil(log(" + changerVal + ")" + conditVal + " - " +
									"log(" + changerVal + ")" + initVal + ")";
				return "T(n)= (" + coefficient + " * " + upperBound + ")" + " + " + residual +
				   		"\n      or\n      " +
				   		"(" + coefficient + " * (" + upperBound + " + 1))" + " + " + residual +
				   		"\n      if there exists an integer x such that " + initVal + " * " + changerVal +
				   		"^x == " + conditVal;
			} else {
				int upperBoundInt = (int) (Math.ceil(log(Integer.valueOf(conditVal), Integer.valueOf(changerVal)) -
						 	log(Integer.valueOf(initVal), Integer.valueOf(changerVal))));
				return "T(n)= " + String.valueOf((coefficientInt * (upperBoundInt + plusOneType2())) + residualInt);
			}
		} else { //inverted type
			if(!initVal.matches("\\d+") || !conditVal.matches("\\d+")) {
				String upperBound = "ceil(log(" + changerVal + ")" + initVal + " - " +
									"log(" + changerVal + ")" + conditVal + ")";
				return "T(n)= (" + coefficient + " * " + upperBound + ")" + " + " + residual +
				   		"\n      or\n      " +
				   		"(" + coefficient + " * (" + upperBound + " + 1))" + " + " + residual +
				   		"\n      if there exists an integer x such that " + conditVal + " * " + changerVal +
				   		"^x == " + initVal;
			} else {
				int upperBoundInt = (int) (Math.ceil(log(Integer.valueOf(initVal), Integer.valueOf(changerVal)) -
						 	log(Integer.valueOf(conditVal), Integer.valueOf(changerVal))));
				return "T(n)= " + String.valueOf((coefficientInt * (upperBoundInt + plusOneType2Inv())) + residualInt);
			}				
		}
	}

	private int plusOneType2() {
		int initValInt = Integer.valueOf(initVal);
		int conditValInt = Integer.valueOf(conditVal);
		int changerValInt = Integer.valueOf(changerVal);

		while(conditValInt >= initValInt) {
			if(conditValInt == initValInt) {
				return 1;
			}
			conditValInt /= changerValInt;
		}
		return 0;
	}

	private int plusOneType2Inv() {
		int initValInt = Integer.valueOf(initVal);
		int conditValInt = Integer.valueOf(conditVal);
		int changerValInt = Integer.valueOf(changerVal);

		while(initValInt >= conditValInt) {
			if(initValInt == conditValInt) {
				return 1;
			}
			initValInt /= changerValInt;
		}
		return 0;		
	}

	private static double log(int x, int y) {
		return ((int)((Math.log(x) / Math.log(y)) * 1000)) / 1000.000;
	}

	/*
	*	Type 3 Solution
	*/
	private String solveType3() {
		if(changerOp.equals("+=") || changerOp.equals("*=")) {
			if(!initVal.matches("\\d+") || !conditVal.matches("\\d+")) {
				return "T(n)= " + String.valueOf(unitTimeCounter(init) + unitTimeCounter(condit)) + 
					   "\n      or\n      " + 
					   "infinite";
			} else {
				if(Integer.valueOf(initVal) >= Integer.valueOf(conditVal)) {
					return "T(n)= infinite";
				} else {
					return "T(n)= " + String.valueOf(unitTimeCounter(init) + unitTimeCounter(condit));
				}
			}
		} else { //inverted
			if(!initVal.matches("\\d+") || !conditVal.matches("\\d+")) {
				return "T(n)= " + String.valueOf(unitTimeCounter(init) + unitTimeCounter(condit)) + 
					   "\n      or\n      " + 
					   "infinite";
			} else {
				if(Integer.valueOf(initVal) <= Integer.valueOf(conditVal)) {
					return "T(n)= infinite";
				} else {
					return "T(n)= " + String.valueOf(unitTimeCounter(init) + unitTimeCounter(condit));
				}
			}			
		}
	}

	/*
	*	Type 4 Solution
	*/
	private String solveType4() {
		String coefficient = getCoefficient();
		String residual = getResidual();

		int coefficientInt = Integer.valueOf(coefficient);
		int residualInt = Integer.valueOf(residual); 

		if(unitTimeCounter(signifCondit) == 2) {
			if(!conditVal.matches("\\d+")) {
				String upperBound = "ceil(sqrt(" + conditVal + "))"; // + -1
				return "T(n)= (" + coefficient + " * " + upperBound + " - 1) + " + residual +
					   "\n      or\n      " + 
					   "(" + coefficient + " * (" + upperBound + ")) + " + residual +
					   "\n      if sqrt(" + conditVal + ") is an integer";
			} else {
				int upperBoundInt = (int) Math.ceil(Math.sqrt(Integer.valueOf(conditVal)) -1);
				return String.valueOf((coefficientInt * (upperBoundInt + plusOneType4())) +
					   residualInt);
			}
		} else { //unitTimeCounter(signifCondit) == 3
			String upperBound = "ceil(cubert(" + conditVal + "))"; // + -1
			if(!conditVal.matches("\\d+")) {
				return "T(n)= (" + coefficient + " * " + upperBound + " - 1) + " + residual +
					   "\n      or\n      " + 
					   "(" + coefficient + " * (" + upperBound + ")) + " + residual +
					   "\n      if cubert(" + conditVal + ") is an integer";
			} else {
				int upperBoundInt = (int) Math.ceil(Math.cbrt(Integer.valueOf(conditVal)) -1);
				return String.valueOf((coefficientInt * (upperBoundInt + plusOneType4_2())) +
					   residualInt);
			}			
		}
	}

	private int plusOneType4() {
		if(Math.sqrt(Integer.valueOf(conditVal)) - 
		   Math.floor(Math.sqrt(Integer.valueOf(conditVal))) == 0) 
		{
			return 1;
		} else {
			return 0;
		}
	}

	private int plusOneType4_2() {
		if(Math.cbrt(Integer.valueOf(conditVal)) - 
		   Math.floor(Math.cbrt(Integer.valueOf(conditVal))) == 0) 
		{
			return 1;
		} else {
			return 0;
		}
	}

	public boolean isInfinite() {
		return (conditOp.equals(">=") && changerOp.equals("+=")) ||
		       (conditOp.equals(">=") && changerOp.equals("*=")) ||
		       (conditOp.equals(">") && changerOp.equals("+="))  ||
		       (conditOp.equals(">") && changerOp.equals("*="))  ||
		   	   (conditOp.equals("<=") && changerOp.equals("-=")) ||  
		   	   (conditOp.equals("<=") && changerOp.equals("/=")) ||
		   	   (conditOp.equals("<") && changerOp.equals("-="))  ||  
		   	   (conditOp.equals("<") && changerOp.equals("/="));
	}	

	public boolean isPowered() {
		return unitTimeCounter(signifCondit) > 1;
	}

	private int unitTimeCounter(String operation) {
		int counter = 0;
        Pattern pattern = Pattern.compile("[\\+*-/=><]?[*=+-/><]");
        Matcher matcher = pattern.matcher(operation);

        while (matcher.find()) {
            counter++;
        }
        return counter;
	}

	private int unitTimeCounter(ArrayList<String> tokenArray) {
		int counter = 0;
        Pattern pattern = Pattern.compile("[\\+*-/=><]?[*=+-/><]");

        for(int i = 0; i < tokenArray.size(); i++) {
        	Matcher matcher = pattern.matcher(tokenArray.get(i));
            while (matcher.find()) {
            	counter++;
        	}
        }
        return counter;
	}
}