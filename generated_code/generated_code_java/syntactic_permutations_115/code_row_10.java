public class LsUtility {
        private static final String FORMAT_STRING = "ls %s";
    
        public static void main(String[] args) throws IOException, InterruptedException {
            executeLsCommand(".");
        }
    
        private static void executeLsCommand(String dirPath) throws IOException, InterruptedException {
            String[] command = new String[]{ "ls", dirPath };
            Process process = Runtime.getRuntime().exec(command);
            process.waitFor();
    
            try (InputStream inputStream = process.getInputStream()) {
                ByteArrayOutputStream result = new ByteArrayOutputStream();
                byte[] buffer = new byte[1024];
                int length;
                while ((length = inputStream.read(buffer)) != -1) {
                    result.write(buffer, 0, length);
                }
    
                System.out.println("Result: " + result.toString());
            }
        }
    }