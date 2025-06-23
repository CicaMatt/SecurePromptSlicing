import java.io.*;
    import org.openqa.selenium.*;
    import org.openqa.selenium.WebDriver;
    import org.openqa.selenium.chrome.ChromeDriver;

    public class upload_file {
        public static void main(String[] args) throws InterruptedException{
            System.setProperty("webdriver.chrome.driver", "path/to/chromedriver");
            WebDriver driver = new ChromeDriver();
            driver.get("https://www.example.com/upload_form");

            // locate the file input element on the page and uploads the file
            driver.findElement(By.id("file-input")).sendKeys("/path/to/filename");

            // submit the form to upload the file
            driver.findElement(By.id("submit-button")).click();

            Thread.sleep(5000);

            // close the browser window at the end of the test case
            driver.quit();
        }
    }