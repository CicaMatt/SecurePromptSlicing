import java.util.Scanner;

public class Add Thousand {
    public static int main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int value = scanner.nextInt();
        value += 1000;
        System.out.println(value);
        return 0;
    }
}