import java.io.File;
    import java.io.FileWriter;
    import java.nio.file.Paths;
    import java.nio.file.Files;
    import java.util.*;

    public class SecretFile {
        public static void main(String[] args) throws Exception{
            String secretInfo = "This is my secret info!";

            File file = new File("secret-info");
            FileWriter writer = new FileWriter(file);

            try{
                writer.write(secretInfo);
            } finally {
                writer.close();
            }

            Files.setAttribute(Paths.get("secret-info"), "posix:permissions", EnumSet.of(PosixFilePermission.OWNER_READ));

            System.out.println(file.getName());
        }
    }