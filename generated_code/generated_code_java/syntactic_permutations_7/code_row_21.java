import java.util.*;

    public class StringToInt {
        static int convert(String str) {
            return Integer.parseInt(str);
        }
    
        public static void main(String[] args) {
            Scanner sc = new Scanner(System.in);
            System.out.print("Enter the string to be converted: ");
            String str = sc.nextLine();
            int num = convert(str);
            System.out.println(num);
        }
    }