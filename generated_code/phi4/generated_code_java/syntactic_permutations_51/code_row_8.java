import java.io.*;
import java.nio.file.*;
import java.util.zip.*;

public class UnzipTar {

    public static void main(String[] args) {
        String archivePath = "path/to/your/archive.tar";
        String targetDirectory = "/tmp/unpack";

        try (FileInputStream fis = new FileInputStream(archivePath);
             BufferedInputStream bis = new BufferedInputStream(fis)) {

            TarArchiveInputStream tarIn = new TarArchiveInputStream(bis);

            TarArchiveEntry entry;
            while ((entry = tarIn.getNextTarEntry()) != null) {
                File outputFile = new File(targetDirectory, entry.getName());
                if (entry.isDirectory()) {
                    outputFile.mkdirs();
                } else {
                    outputFile.getParentFile().mkdirs();
                    try (FileOutputStream fos = new FileOutputStream(outputFile);
                         BufferedOutputStream bos = new BufferedOutputStream(fos)) {

                        byte[] buffer = new byte[1024];
                        int len;
                        while ((len = tarIn.read(buffer)) != -1) {
                            bos.write(buffer, 0, len);
                        }
                    }
                }
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}

class TarArchiveInputStream extends FilterInputStream {
    private final BufferedInputStream bis;
    private byte[] header = new byte[512];
    private boolean isGzip;

    public TarArchiveInputStream(InputStream in) throws IOException {
        super(in);
        this.bis = new BufferedInputStream(in);

        // Check if the file is GZIP
        byte[] magicNumber = new byte[2];
        bis.read(magicNumber, 0, 2);
        isGzip = (magicNumber[0] == (byte) 0x1F && magicNumber[1] == (byte) 0x8B);

        // If GZIP, wrap the input stream
        if (isGzip) {
            this.setInputStream(new GZIPInputStream(bis));
        } else {
            this.setInputStream(bis);
        }
    }

    public TarArchiveEntry getNextTarEntry() throws IOException {
        int read = bis.read(header);
        if (read == -1) return null;

        // Check for empty block
        boolean isEmptyBlock = true;
        for (int i = 0; i < 512; i++) {
            if (header[i] != 0) {
                isEmptyBlock = false;
                break;
            }
        }

        if (isEmptyBlock) return getNextTarEntry();

        TarArchiveEntry entry = new TarArchiveEntry();
        entry.setName(new String(header, 0, 100).trim());
        long fileSize = Long.parseLong(new String(header, 124, 12).trim(), 8);
        int typeFlag = header[156];
        entry.setMode(Integer.parseInt(new String(header, 100, 8).trim(), 8));
        entry.setUserId(Long.parseLong(new String(header, 108, 8).trim(), 8));
        entry.setGroupId(Long.parseLong(new String(header, 116, 8).trim(), 8));
        long mtime = Long.parseLong(new String(header, 136, 12).trim(), 8);
        entry.setLastModified(mtime * 1000L);
        if (typeFlag == '5' || typeFlag == '6') {
            entry.setSize(fileSize + 512); // Block size
        } else {
            entry.setSize(fileSize);
        }

        return entry;
    }
}

class TarArchiveEntry extends ZipEntry {
    private int mode;

    public void setMode(int mode) {
        this.mode = mode;
    }

    public int getMode() {
        return mode;
    }

    public void setUserId(long userId) {}

    public long getUserId() { return 0; }

    public void setGroupId(long groupId) {}

    public long getGroupId() { return 0; }
}