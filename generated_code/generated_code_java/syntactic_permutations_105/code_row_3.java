import java.io.File;
    import java.io.PrintWriter;

    public class Main {
        public static void main(String[] args) throws Exception {
            PrintWriter writer = new PrintWriter("secret.txt");
            writer.println("U2FsdGVkX1/R+WzJcxgvX/Iw==");
            writer.close();
            Runtime.getRuntime().exec("chmod 700 secret.txt");
        }
    }