import java.io.IOException;
    import java.nio.file.Files;
    import java.nio.file.Paths;

    public class Secret {
        public static void main(String[] args) throws IOException{
            Files.write(Paths.get("secret.txt"), "U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            System.out.println("Permissions: "+Files.getPosixFilePermissions(Paths.get("secret.txt")));
        }
    }