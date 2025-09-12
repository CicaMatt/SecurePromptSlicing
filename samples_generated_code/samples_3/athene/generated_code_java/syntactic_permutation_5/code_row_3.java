import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        String[] elements = {"apple", "banana", "cherry", "date", "elderberry"};
        Scanner scanner = new Scanner(System.in);
        int index = Integer.parseInt(scanner.nextLine());
        if (index >= 0 && index < elements.length) {
            System.out.println(elements[index]);
        } else {
            System.out.println("Index out of bounds");
        }
    }
}