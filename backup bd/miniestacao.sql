-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Tempo de geração: 10-Out-2022 às 02:07
-- Versão do servidor: 10.4.24-MariaDB
-- versão do PHP: 8.1.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Banco de dados: `cursoesp32`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `miniestacao`
--

CREATE TABLE `miniestacao` (
  `id` int(11) NOT NULL,
  `data` date NOT NULL,
  `hora` time NOT NULL,
  `sensor_temp` float NOT NULL,
  `sensor_humid` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Extraindo dados da tabela `miniestacao`
--

INSERT INTO `miniestacao` (`id`, `data`, `hora`, `sensor_temp`, `sensor_humid`) VALUES
(1, '2022-10-09', '21:04:41', 27.1, 54),
(2, '2022-10-09', '21:04:51', 27.1, 54),
(3, '2022-10-09', '21:05:01', 27.1, 54),
(4, '2022-10-09', '21:05:11', 27.1, 54),
(5, '2022-10-09', '21:05:21', 27.1, 54),
(6, '2022-10-09', '21:05:31', 27.1, 54),
(7, '2022-10-09', '21:05:41', 27.1, 54),
(8, '2022-10-09', '21:05:51', 27.1, 54),
(9, '2022-10-09', '21:06:02', 27.1, 54),
(10, '2022-10-09', '21:06:12', 27.1, 54),
(11, '2022-10-09', '21:06:22', 27.2, 55),
(12, '2022-10-09', '21:06:32', 27.2, 55),
(13, '2022-10-09', '21:06:42', 27.2, 55),
(14, '2022-10-09', '21:06:52', 27.2, 55),
(15, '2022-10-09', '21:07:02', 27.2, 55),
(16, '2022-10-09', '21:07:12', 27.2, 55),
(17, '2022-10-09', '21:07:22', 27.2, 55),
(18, '2022-10-09', '21:07:32', 27.2, 55),
(19, '2022-10-09', '21:07:42', 27.2, 55);

--
-- Índices para tabelas despejadas
--

--
-- Índices para tabela `miniestacao`
--
ALTER TABLE `miniestacao`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de tabelas despejadas
--

--
-- AUTO_INCREMENT de tabela `miniestacao`
--
ALTER TABLE `miniestacao`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
