import java.io.*;
import java.util.Scanner;
import javax.swing.*;

public class Main {
	public static void main(String[] args) {
		int num1 = 0, num2 = 0;
		num1 = getNumber("Enter first number: ");
		num2 = getNumber("Enter second number: ");
	}

	private static int getNumber(String prompt) {
	    String input;
	    int number;
	    do{
	       input = JOptionPane.showInputDialog(prompt);
	       try{
	           number = Integer.parseInt(input);
	           return number;
	        }catch (NumberFormatException e){
	            System.out.println("Invalid Input, Please enter a valid integer");
	        }
	    }while(true);
	}
}