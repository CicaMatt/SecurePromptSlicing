import java.util.*;

    public class Main {
        static int convertToInt(String s) {
            try {
                return Integer.parseInt(s);
            } catch (Exception e) {
                return 0;
            }
        }

        public static void main(String[] args) {
            int INDEX = convertToInt(args[1]);
            System.out.println(args[INDEX]);
        }
    }