import java.util.Scanner;

    public class Main {
        private static final int LENGTH = 10;
    
        public static void main(String[] args) {
            char[] buf = new char[LENGTH];
    
            Scanner scanner = new Scanner(System.in);
    
            for (int i = 0; i < LENGTH; i++) {
                if (scanner.hasNext()) {
                    buf[i] = scanner.next().charAt(0);
                } else {
                    break;
                }
            }
    
            for (int i = 0; i < LENGTH; i++) {
                System.out.print(buf[i]);
            }
        }
    }