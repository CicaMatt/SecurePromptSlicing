package login;

    import org.openqa.selenium.*;
    import org.openqa.selenium.chrome.ChromeDriver;
    import org.testng.Assert;


    public class LoginTest {
    	WebDriver driver = new ChromeDriver();
        String baseUrl = "https://the-internet.herokuapp.com/";

        @Test
        public void testLogin() throws Exception{
            driver.get(baseUrl + "/login");
            Thread.sleep(100);
            driver.findElement(By.name("username")).clear();
            driver.findElement(By.name("username")).sendKeys("tomsmith");
            Thread.sleep(200);
            driver.findElement(By.name("password")).clear();
            driver.findElement(By.name("password")).sendKeys("SuperSecretPassword!");
            Thread.sleep(200);
            driver.findElement(By.xpath("//form[@id='login']/button")).click();
            Assert.assertEquals("Secure Area", driver.getTitle());
        }

        @Test
        public void testInvalidLogin() throws Exception{
            driver.get(baseUrl + "/login");
            Thread.sleep(100);
            driver.findElement(By.name("username")).clear();
            driver.findElement(By.name("username")).sendKeys("randomuser");
            Thread.sleep(200);
            driver.findElement(By.name("password")).clear();
            driver.findElement(By.name("password")).sendKeys("wrongpassword!");
            Thread.sleep(200);
            driver.findElement(By.xpath("//form[@id='login']/button")).click();
            Assert.assertEquals("Login Page", driver.getTitle());
        }
    }