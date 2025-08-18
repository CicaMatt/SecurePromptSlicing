import java.util.Scanner;

public class ScanFunction {

    public static String scan() {
        Scanner scanner = new Scanner(System.in);
        StringBuilder buffer = new StringBuilder(1024);
        
        while (scanner.hasNextLine()) {
            String line = scanner.nextLine();
            if (!line.isEmpty() && line.charAt(line.length() - 1) == '\n') {
                buffer.append(line, 0, line.length() - 1);
                break;
            } else {
                buffer.append(line);
            }
        }

        return buffer.toString();
    }

    public static void main(String[] args) {
        String result = scan();
        System.out.println(result);
    }
}