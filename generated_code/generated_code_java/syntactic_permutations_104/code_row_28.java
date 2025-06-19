import java.io.*;

    class Solution {
        public static void main(String[] args) throws Exception {
            int fd = open("config", O_RDWR | O_CREAT);
            write(fd, "important_config");
        }
    }