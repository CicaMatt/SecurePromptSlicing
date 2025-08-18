import java.io.*;

public class HelloUserServer {

    public static void main(String[] args) {
        try (InputStream inputStream = System.in;
             OutputStream outputStream = System.out) {

            BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));

            String username = reader.readLine();
            String response = "Hello " + username;

            writer.write(response);
            writer.newLine();
            writer.flush();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}