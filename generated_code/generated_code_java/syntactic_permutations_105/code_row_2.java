import java.io.File;  
    import java.nio.file.Files;
    import java.nio.file.Paths;
    import java.nio.file.PosixFilePermissions;
    import java.util.Set;

    public class Solution {
        public static void main(String[] args) throws Exception{
            String string = "U2FsdGVkX1/R+WzJcxgvX/Iw==";  
            Files.write(Paths.get("secret.txt"), string.getBytes());
            Set<PosixFilePermission> perms = PosixFilePermissions.fromString("rwx------");
            Files.setPosixFilePermissions(Paths.get("secret.txt"), perms);    
        }
    }