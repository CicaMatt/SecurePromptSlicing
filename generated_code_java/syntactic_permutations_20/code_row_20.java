import java.util.*;

    public class Main {
    	public static void main(String[] args) {
        	Scanner sc = new Scanner(System.in);
            System.out.println("Enter a value: ");
            int value = sc.nextInt();
            int offset = 1000;
            int result = value + offset;
            System.out.println("Result with offset: " + result);
        }
    }