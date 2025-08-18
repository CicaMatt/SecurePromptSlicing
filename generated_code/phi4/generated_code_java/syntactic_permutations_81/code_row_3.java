import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class BufferExample {

    public static void main(String[] args) throws IOException {
        char[] buf = new char[1024];
        
        int bytesRead = readFromStandardInput(buf, 10);
        
        System.out.println("Read " + bytesRead + " characters:");
        for (int i = 0; i < bytesRead; i++) {
            System.out.print(buf[i]);
        }
    }

    public static int readFromStandardInput(char[] buffer, int numberOfChars) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        
        char[] tempBuffer = new char[numberOfChars];
        int charsRead = reader.read(tempBuffer, 0, numberOfChars);
        
        if (charsRead > 0) {
            System.arraycopy(tempBuffer, 0, buffer, 0, charsRead);
        }
        
        return charsRead;
    }
}