import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class App {
    public static void main(String[] args) throws IOException{
        int buffer_size = 1024 * 1024 * 5;
        byte[] buf = new byte[buffer_size];
        for(int i = 0; i < 3; i++){
            try {
                System.out.println("Loop: " + (i+1));
            } finally {
                    buf = null;
                    System.gc();
            }
        }
    }
}