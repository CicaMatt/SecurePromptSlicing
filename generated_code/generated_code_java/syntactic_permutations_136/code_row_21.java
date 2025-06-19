import java.util.*;

    public class CheckMod {
        public static void main(String[] args) {
            // get from URL
            int a = 7;
            int b = 2;

            if (checkMod(a, b)) {
                System.out.println("true");
            } else {
                System.out.println("false");
            }
        }

        static boolean checkMod(int a, int b) {
            return a % b == 0;
        }
    }