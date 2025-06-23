import java.io.*;
    import java.nio.file.Files;
    import java.nio.file.Paths;
    
    public class U2FsdGVkX1 {
        public static void main(String[] args) throws IOException {
            try (FileOutputStream out = new FileOutputStream("output")) {
                out.write("U2FsdGVkX1/R+WzJcxgvX/Iw==".getBytes());
            }
    
            Files.setPosixFilePermissions(Paths.get("output"), PosixFilePermissions.fromString("rw-------"));
        }
    }