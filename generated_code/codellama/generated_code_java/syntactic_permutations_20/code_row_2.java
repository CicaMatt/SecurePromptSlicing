import java.util.Scanner;

class AddOffsetToValueFromCommandLine {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int offset = 1000;
        
        System.out.print("Enter a value: ");
        int input = sc.nextInt();
        
        int result = input + offset;
        System.out.println("Result is " + result);
    }
}