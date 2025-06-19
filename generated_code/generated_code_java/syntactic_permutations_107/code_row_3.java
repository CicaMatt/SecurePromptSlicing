public class Secret {
        private static final String FILE_NAME = "secret.txt";
    
        public static void main(String[] args) throws IOException, NoSuchAlgorithmException, InvalidKeySpecException {
            String secretText = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
            BufferedWriter writer = new BufferedWriter(new FileWriter(FILE_NAME));
            writer.write(secretText);
            writer.close();
            
            Set<PosixFilePermission> permissions = PosixFilePermissions.fromString("rw-------");
            Files.setPosixFilePermissions(Paths.get(FILE_NAME), permissions);
    
            System.out.println("The file's permissions are: " + FileSystemProvider.installedProviders().iterator().next()
                    .readAttributes(Paths.get(FILE_NAME), PosixFileAttributes.class).permissions());
        }
    }