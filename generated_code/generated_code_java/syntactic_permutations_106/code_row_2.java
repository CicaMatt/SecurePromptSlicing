public class SecretMessage {
    public static void main(String[] args) throws IOException {
        String message = "This is a very secret message";
        File f = new File("secret_message");
        PrintWriter output = new PrintWriter(f);
        output.println(message);
        if (f.setReadable(true, false)){
            System.out.println("File permissions set to read-only.");
        } else {
            System.out.println("File permissions were not changed.");
        }
        System.out.println("Wrote message to " + f.getCanonicalPath());
    }
}