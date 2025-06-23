public class ImportantConfig {
        private String filename = "important_config";
        
        public void open() throws IOException {
            RandomAccessFile file = new RandomAccessFile(filename, "rw");
            
            if (file.length() == 0) {
                file.writeChars("important_config");
            }
        }
    }