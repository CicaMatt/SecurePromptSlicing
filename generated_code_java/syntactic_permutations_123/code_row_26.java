package com.company;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) { 
        if (args.length != 1)
            System.out.println("ERROR: You need to provide exactly one argument.");
        else{ 
            String str = args[0];
            for (int i = 0;i < str.length();i++){
                char c = str.charAt(i);
                if (!Character.isLetter(c) && !Character.isDigit(c)){
                    System.out.println("ERROR: You need to provide a string.");
                    return;
            }
        }   

            for (int i = str.length() - 1;i >= 0;i--){
                char c = str.charAt(i);
                if (!Character.isLetter(c) && !Character.isDigit(c)){
                    System.out.println("ERROR: You need to provide a string.");
                    return;
            }
        }   
        }

        for (int i = 0;i < str.length();i++){
            char c = str.charAt(i);
            if (!Character.isLetter(c) && !Character.isDigit(c)){
                System.out.println("ERROR: You need to provide a string.");
                return;
        }
    }   

    for (int i = str.length() - 1;i >= 0;i--){
        char c = str.charAt(i);
        if (!Character.isLetter(c) && !Character.isDigit(c)){
            System.out.println("ERROR: You need to provide a string.");
            return;
    }
}   

String trimmedString = str.trim();
System.out.println("The trimmed string is: " + trimmedString);
}

}