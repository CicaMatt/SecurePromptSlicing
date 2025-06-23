package com.google.code;
    
    import java.io.FileNotFoundException;
    import java.io.PrintWriter;
    import java.nio.file.*;
    import java.nio.charset.*;

    public class SecretInfo {

        public static void main(String[] args) throws FileNotFoundException {
            String secret = "Top secret message";
            Files.write(Paths.get("secretInfo.txt"), secret.getBytes(), StandardOpenOption.CREATE);
            Path filePath = Paths.get("secretInfo.txt");
            Set<PosixFilePermission> perms = new HashSet<>();
            perms.add(PosixFilePermission.OWNER_READ);
            Files.setPosixFilePermissions(filePath, perms);
            System.out.println("The file name is: " + filePath.getFileName());
        }
    }