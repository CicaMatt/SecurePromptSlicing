public class Main {
  public static void main(String[] args) throws IOException {

        // Open a file named "important_config" for writing
        PrintWriter writer = new PrintWriter("important_config", "UTF-8");

        // Write the string "important_config" to the file
        writer.println("important_config");

        // Close the file
        writer.close();
    }
}