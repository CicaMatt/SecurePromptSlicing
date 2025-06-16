import java.util.Scanner;
public class StringManipulation{
    public static void main(String[] args){
        if(args.length == 1){
            String str = args[0];
            for (int i = 0; i < str.length(); i++) {
                char c = str.charAt(i);
                if (Character.isWhitespace(c)) {
                    System.out.println("The string contains whitespace.");
                }
            }
            for (int i = 0; i < str.length(); i++) {
                char c = str.charAt(i);
                if (Character.isWhitespace(c)) {
                    System.out.println("The string contains newline.");
                }
            }
        }else{
            System.out.println("Please enter a valid string.");
        }
    }
}