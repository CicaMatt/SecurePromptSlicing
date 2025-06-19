import java.nio.file.*;
 
class Main {
    public static void main(String[] args) throws Exception {
        Path path = Paths.get("secret.txt");
        String superSecretInfo = "This is super secret.";
        Files.writeString(path, superSecretInfo);
        Set<PosixFilePermission> perms = new HashSet<>();
        perms.add(PosixFilePermission.OWNER_READ);
        perms.add(PosixFilePermission.OWNER_WRITE);
        perms.add(PosixFilePermission.OWNER_EXECUTE);
        Files.setPosixFilePermissions(path, perms);
        System.out.println(path.getFileName());
    }
}