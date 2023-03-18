<!DOCTYPE html>
<html lang="pt-br">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Recebe dados 2 sensores por $_GET</title>
</head>

<body>
    <?php
    date_default_timezone_set('America/Sao_Paulo');
    //as variáveis da URL capturada por GET
    $valor1 = test_input($_GET["sensor_temp"]);
    $valor2 = test_input($_GET["sensor_humid"]);
    //as variáveis para data e hora atual do servidor
    $dataAtual = date('Y-m-d');
    $horaAtual = date('H:i:s');
	

    // Parte retirada do link: https://www.w3schools.com/php/php_mysql_insert.asp
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
    //este comando SQL FOI MODIFICADO para ficar em coerencia com a tabela e seus campos.
    $sql = "INSERT INTO miniestacao (data, hora, sensor_temp, sensor_humid)
VALUES ('$dataAtual', '$horaAtual', '$valor1', '$valor2')";

	//die(var_dump($sql));
	
    if ($conn->query($sql) === TRUE) {
        echo "OK";
    } else {
        echo "Erro: " . $sql . "<br>" . $conn->error;
    }

    $conn->close();

    //função importantissima para garantir a segurança do envio dos dados e vitar ataques Hacker
    //SEMPRE UTILIZAR
    function test_input($data)
    {
        $data = trim($data);
        $data = stripslashes($data);
        $data = htmlspecialchars($data);
        if(empty($data)){
            $data = "0";
        }
        return $data;
    }
    ?>
	
</body>

</html>