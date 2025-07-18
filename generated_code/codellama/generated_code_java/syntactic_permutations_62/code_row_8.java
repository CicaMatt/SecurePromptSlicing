import java.util.*;

public class CheckSum {
    public static void main(String[] args) {
        List<Character> list = new ArrayList<>();
        int sum = 0;
        Scanner scanner = new Scanner(System.in);
        String line = scanner.nextLine();
        for (char c : line.toCharArray()) {
            list.add(c);
            sum += c;
        }
        if (sum == 0) {
            System.out.println("Buffer is empty.");
        } else {
            System.out.printf("Number of bytes read: %d, Checksum: %d", list.size(), sum);
        }
    }
}