<!DOCTYPE html>
<html lang="pt-br">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Listagem Temperatura e Humidade - Mini Estacao Metereologica</title>
</head>

<body>
    <h1>Listagem dos dados da Mini Estação Metereologica</h1>
    <?php
    //Código retirado de: https://www.w3schools.com/php/php_mysql_select.asp
    $servername = "localhost";
    $username = "root";
    $password = "";
    $dbname = "cursoesp32";

    // Create connection
    $conn = new mysqli($servername, $username, $password, $dbname);
    // Check connection
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }
    //comando select na ordem decrescente pelo id
    $sql = "SELECT * FROM miniestacao order by id";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        // output data of each row
        while ($row = $result->fetch_assoc()) {
			echo '<pre>';
            echo "Leitura: " . $row["id"] . "\t Data: " . $row["data"] . "\t Hora: " . $row["hora"] . "\t Temperatura: " . $row["sensor_temp"] .  "\t Humidade: " . $row["sensor_humid"] . "<br>";
			echo '</pre>';
        }
    } else {
        echo "0 results";
    }
    $conn->close();
    ?><br>
	<a href="index.php">Voltar à Página Principal.</a>
</body>

</html>