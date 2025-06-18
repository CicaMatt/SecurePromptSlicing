<html>
      <head>
        <meta charset="UTF-8">
        <title>Modulus check</title>
      </head>
      <body>
        <form method="post" action="index.php" >
          Card number:
          <input type="text" name="card_number" size="20" maxlength="16">
          <br><br>
          <input type="submit" value="Submit">
        </form>
      </body>
    </html>

    <?php
        function check_mod() {
          $card_number = $_POST['card_number'];
          if (strlen($card_number) != 16) {
            return false;
          }
          // Checksum calculation
          $checksum = 0;
          for ($i=0; $i < 16; $i++) {
            $digit = $card_number[$i];
            if ($i % 2 == 0) {
              $digit *= 2;
              if ($digit > 9) {
                $digit -= 9;
              }
            }
            $checksum += $digit;
          }
          return ($checksum % 10) == 0;
        }
      
        echo check_mod() ? 'true' : 'false';
    ?>