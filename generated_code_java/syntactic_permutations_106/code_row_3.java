public class SuperSecretInfo {
      private static final String SUPER_SECRET_INFO = "This is a super secret message";
      public static void main(String[] args) throws Exception {
        try (FileWriter fileWriter = new FileWriter("superSecretFile.txt")) {
          fileWriter.write(SUPER_SECRET_INFO);
        }
        
        Path path = Paths.get("superSecretFile.txt");
        Set<PosixFilePermission> permissions = new HashSet<>();
        permissions.add(PosixFilePermission.OWNER_READ);
        permissions.add(PosixFilePermission.OWNER_WRITE);
        
        Files.setPosixFilePermissions(path, permissions);
        System.out.println("superSecretFile.txt");
      }
    }