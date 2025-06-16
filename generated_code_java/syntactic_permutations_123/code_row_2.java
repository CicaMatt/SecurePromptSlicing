public class HelloWorld {
        public static void main(String[] args) {
            if (args.length == 1){
                String str = args[0];
                for (int i=0;i<str.length();++i){
                    char c = str.charAt(i);
                    if (c != ' ' && c != '\t'){
                        System.out.print(c);
                    }
                }
                for (int i=str.length()-1;i>=0;--i){
                    char c = str.charAt(i);
                    if (c != '\n' && c !='\r'){
                        System.out.print(c);
                    }
                }
            }
        }
    }