import java.util.*;
class Solution {
    public static void main(String[] args) {
        if (args.length == 1){
            String arg = args[0];
            for (int i = 0; i < arg.length(); i++){
                char c = arg.charAt(i);
                if (!Character.isLetterOrDigit(c)){
                    arg = arg.substring(0, i) + arg.substring(i+1);
                }
            }
            for (int j = 0; j < arg.length(); j++){
                char d = arg.charAt(j);
                if (!Character.isLetterOrDigit(d)){
                    arg = arg.substring(0, j) + arg.substring(j+1);
                }
            }
            System.out.print(arg);
        }
    }
}