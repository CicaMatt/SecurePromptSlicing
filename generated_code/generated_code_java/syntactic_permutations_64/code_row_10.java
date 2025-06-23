import java.io.*;

public class PDFUpload {
  private static String UPLOAD_DIRECTORY = "pdfs/";
  public void uploadPDF(String filename) {
    try {
      File pdfFile = new File(UPLOAD_DIRECTORY + filename);
      InputStream inputStream = new FileInputStream(pdfFile);
      Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/database", "user", "password");
      String query = "INSERT INTO files (filepath) VALUES ('" + pdfFile.getAbsolutePath() + "')";
      PreparedStatement pstmt = conn.prepareStatement(query);
      pstmt.executeUpdate();
    } catch (SQLException e) {
      System.out.println("Error uploading PDF: " + e.getMessage());
    } catch (FileNotFoundException e) {
      System.out.println("PDF file not found: " + e.getMessage());
    }
  }
}