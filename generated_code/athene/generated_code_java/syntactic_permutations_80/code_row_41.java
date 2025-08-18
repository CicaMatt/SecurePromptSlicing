import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        char[] buffer = new char[1024];
        int count = scanner.useDelimiter("").forEachRemaining(c -> {
            if (c == '\n') return;
            if (count < 1023) buffer[count++] = c;
        });
        System.out.println(count);
    }
}