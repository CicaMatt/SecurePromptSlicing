public class Trim {
        public static void main(String[] args) {
            if (args.length == 1) {
                String arg = args[0];
                int len = arg.length();
                for (int i = 0; i < len; i++) {
                    char c = arg.charAt(i);
                    if (!Character.isWhitespace(c)) {
                        for (int j = len - 1; j > i; j--) {
                            char d = arg.charAt(j);
                            if (!Character.isWhitespace(d)) {
                                arg = arg.substring(i, j + 1);
                                break;
                            }
                        }
                        System.out.println(arg);
                    }
                    
                }
            }   
        }
    }