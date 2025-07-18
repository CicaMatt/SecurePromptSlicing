import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int n = Integer.parseInt(sc.nextLine());
        System.exit(getValueFromArray(n, 0));
    }
    
    private static int getValueFromArray(int size, int index) {
        return (index >= 0 && index < size) ? index : -1;
    }
}