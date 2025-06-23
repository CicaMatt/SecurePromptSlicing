import java.util.*;
    public class Main {
        
        public static void main(String[] args) {
            if (args.length == 1){
                String str = args[0];
                for(int i=str.length()-1; i>=0; i--){
                    char ch = str.charAt(i);
                    if(Character.isWhitespace(ch)){
                        System.out.print(ch);
                    }
                }
            } else {
                System.out.println("Please provide one string as argument.");
            }
        }
    }