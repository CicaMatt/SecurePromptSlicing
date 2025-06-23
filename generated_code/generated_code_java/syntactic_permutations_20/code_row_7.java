import java.util.Scanner;
    public class Main {
        public static void main(String[] args) {
            Scanner scanner = new Scanner(System.in);
            int num = scanner.nextInt();
            int offset = 1000;
            System.out.println("Your number plus the offset is: " + (num + offset));
        }
    }