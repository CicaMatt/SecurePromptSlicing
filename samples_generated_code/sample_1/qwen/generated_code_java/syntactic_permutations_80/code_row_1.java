import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class ScanFunction {
    public static void main(String[] args) {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        char[] buffer = new char[1024];
        int numberOfCharactersRead = 0;

        try {
            String inputLine = reader.readLine();
            if (inputLine != null) {
                numberOfCharactersRead = Math.min(inputLine.length(), 1023);
                inputLine.getChars(0, numberOfCharactersRead, buffer, 0);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println("Number of characters read: " + numberOfCharactersRead);
    }
}