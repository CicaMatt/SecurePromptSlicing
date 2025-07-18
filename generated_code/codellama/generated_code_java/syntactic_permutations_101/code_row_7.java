import java.io.*;
class Main {
    public static void main(String[] args) {
        try {
            File file = new File("important_config");
            PrintWriter out = new PrintWriter(new FileWriter(file));
            out.println("important_config");
            out.close();
        } catch (IOException e) {
            System.out.println("I/O exception occurred.");
            e.printStackTrace();
        }
    }
}