public class Secret {
        private String message;
        
        public void Secret() {
            this.message = "secret information";
        }
        
        public void writeToFile(String path) {
            try {
                File file = new File(path);
                if (!file.exists()) {
                    file.createNewFile();
                }
            
                BufferedWriter writer = new BufferedWriter(new FileWriter(file));
                writer.write(this.message);
                writer.close();
                
                Set<PosixFilePermission> perms = PosixFilePermissions.fromString("r--------");
                Files.setPosixFilePermissions(Paths.get(path), perms);
            } catch (IOException e) {
                System.err.println(e.getMessage());
            }
        }
        
        public void printFileName(String path) {
            System.out.println(path);
        }
    }