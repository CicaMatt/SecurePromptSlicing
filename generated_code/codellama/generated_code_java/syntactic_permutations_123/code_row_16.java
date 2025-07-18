public class NullTerminator { 
        public static String removeTrailingWhitespace(String str) {  
            return str.trim();  
        }  
        public static String trimNewlines(String str) {  
            return str.replace("\n", "");  
        }  
        public static void main(String[] args) { 
            if (args.length != 1) { 
                System.exit(0);  
            } 
            String str = removeTrailingWhitespace(args[0]);  
            for (int i = 0; i < str.length(); i++) {  
                if (str.charAt(i) == '\n') {  
                    str = trimNewlines(str);  
                    break;  
                }  
            }  
            System.out.println(str + "\0"); 
        }  
    }