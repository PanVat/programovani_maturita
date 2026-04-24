-- phpMyAdmin SQL Dump
-- version 3.3.9
-- http://www.phpmyadmin.net
--
-- Počítač: localhost
-- Vygenerováno: Čtvrtek 27. března 2014, 23:13
-- Verze MySQL: 5.5.8
-- Verze PHP: 5.3.5

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Databáze: `langschool`
--

-- --------------------------------------------------------

--
-- Struktura tabulky `jazyk`
--

CREATE TABLE IF NOT EXISTS `jazyk` (
  `zkratka` varchar(3) COLLATE utf8_czech_ci NOT NULL,
  `oznaceni` varchar(45) COLLATE utf8_czech_ci NOT NULL,
  PRIMARY KEY (`zkratka`),
  KEY `jazyk` (`oznaceni`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `jazyk`
--

INSERT INTO `jazyk` (`zkratka`, `oznaceni`) VALUES
('ANJ', 'Angličtina'),
('FRJ', 'Francouzština'),
('ITJ', 'Italština'),
('NEJ', 'Němčina'),
('RUJ', 'Ruština'),
('SPJ', 'Španělština');

-- --------------------------------------------------------

--
-- Struktura tabulky `jazyk_lektoru`
--

CREATE TABLE IF NOT EXISTS `jazyk_lektoru` (
  `lektor` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `jazyk` varchar(3) COLLATE utf8_czech_ci NOT NULL,
  PRIMARY KEY (`lektor`,`jazyk`),
  KEY `fk_lektor_has_jazyk_jazyk1_idx` (`jazyk`),
  KEY `fk_lektor_has_jazyk_lektor1_idx` (`lektor`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `jazyk_lektoru`
--

INSERT INTO `jazyk_lektoru` (`lektor`, `jazyk`) VALUES
('bassova', 'ANJ'),
('coburn', 'ANJ'),
('grey', 'ANJ'),
('coburn', 'FRJ'),
('hruby', 'FRJ'),
('lopez', 'FRJ'),
('hruby', 'ITJ'),
('bassova', 'NEJ'),
('bassova', 'RUJ'),
('petruskin', 'RUJ'),
('lopez', 'SPJ');

-- --------------------------------------------------------

--
-- Struktura tabulky `kurz`
--

CREATE TABLE IF NOT EXISTS `kurz` (
  `idkurz` int(5) unsigned zerofill NOT NULL AUTO_INCREMENT,
  `nazev` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL,
  `datum_zahajeni` date DEFAULT NULL,
  `pocet_lekci` int(11) DEFAULT NULL,
  `datum_ukonceni` date DEFAULT NULL,
  `lektor` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `jazyk` varchar(3) COLLATE utf8_czech_ci NOT NULL,
  `ucebna_oznaceni` varchar(5) COLLATE utf8_czech_ci NOT NULL,
  `uroven` enum('začátečníci','pokročilí') COLLATE utf8_czech_ci DEFAULT NULL,
  PRIMARY KEY (`idkurz`),
  KEY `fk_kurz_lektor1_idx` (`lektor`),
  KEY `fk_kurz_jazyk1_idx` (`jazyk`),
  KEY `fk_kurz_ucebna1_idx` (`ucebna_oznaceni`),
  KEY `nazev` (`nazev`),
  KEY `zahajeni` (`datum_zahajeni`),
  KEY `pocet_lekci` (`pocet_lekci`),
  KEY `ukonceni` (`datum_ukonceni`),
  KEY `uroven` (`uroven`)
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci AUTO_INCREMENT=9 ;

--
-- Vypisuji data pro tabulku `kurz`
--

INSERT INTO `kurz` (`idkurz`, `nazev`, `datum_zahajeni`, `pocet_lekci`, `datum_ukonceni`, `lektor`, `jazyk`, `ucebna_oznaceni`, `uroven`) VALUES
(00001, 'Byznys angličtina', '2010-01-05', 15, '2010-06-01', 'grey', 'ANJ', 'UC02', 'pokročilí'),
(00002, 'Učíme se německy', '2010-03-01', 10, '2010-06-30', 'bassova', 'NEJ', 'UC01', 'začátečníci'),
(00003, 'Základy španělštiny', '2012-03-14', 10, '2012-08-13', 'lopez', 'SPJ', 'UC03', 'začátečníci'),
(00004, 'Angličtina pro pokročilé', '2012-04-12', 20, '2012-07-19', 'grey', 'ANJ', 'UC02', 'pokročilí'),
(00005, 'Angličtina snadno a rychle', '2014-03-03', 10, NULL, 'bassova', 'ANJ', 'UC03', 'začátečníci'),
(00006, 'Ruština pro dobrodruhy', '2014-03-25', 10, NULL, 'petruskin', 'RUJ', 'UC02', 'začátečníci'),
(00007, 'Śpanělsky s prstem v nose', '2014-04-23', 10, NULL, 'lopez', 'SPJ', 'UC02', 'pokročilí'),
(00008, 'Angličtina - nic jednoduššího', '2014-04-08', 15, NULL, 'grey', 'ANJ', 'UC02', 'začátečníci');

-- --------------------------------------------------------

--
-- Struktura tabulky `lektor`
--

CREATE TABLE IF NOT EXISTS `lektor` (
  `uzivatel_nick` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `studium` text COLLATE utf8_czech_ci,
  `foto` blob,
  `rodily_mluvci` enum('ano','ne') COLLATE utf8_czech_ci DEFAULT NULL,
  PRIMARY KEY (`uzivatel_nick`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `lektor`
--

INSERT INTO `lektor` (`uzivatel_nick`, `studium`, `foto`, `rodily_mluvci`) VALUES
('bassova', NULL, NULL, 'ne'),
('coburn', NULL, NULL, 'ano'),
('grey', 'Oxford University 2005', NULL, 'ano'),
('hruby', NULL, NULL, 'ne'),
('lopez', NULL, NULL, 'ano'),
('petruskin', NULL, NULL, 'ano');

-- --------------------------------------------------------

--
-- Struktura tabulky `student`
--

CREATE TABLE IF NOT EXISTS `student` (
  `uzivatel_nick` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `cislo_konta` varchar(20) COLLATE utf8_czech_ci DEFAULT NULL,
  PRIMARY KEY (`uzivatel_nick`),
  UNIQUE KEY `cislo_konta_UNIQUE` (`cislo_konta`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `student`
--

INSERT INTO `student` (`uzivatel_nick`, `cislo_konta`) VALUES
('vojir', '00040096/0300'),
('husnik', '00991001/0200'),
('packal', '01677413/0500'),
('sperk', '02317002/0600'),
('seidlova', '02331133/0300'),
('troufal', '03029159/0200'),
('sobota', '03093699/0200'),
('lebeda', '03183523/0300'),
('sekyra', '03372310/0300'),
('volna', '03499405/0300'),
('hilsky', '03663331/0300'),
('frejova', '03792406/0400'),
('pilna', '03820220/0400'),
('svetly', '04142001/0600'),
('novak', '04227848/0400'),
('tluchor', '05279324/0500'),
('hornak', '05471630/0500'),
('pleva', '07487468/0100'),
('rybnicek', '07879913/0600'),
('stalinek', '08157632/0300'),
('soudkova', '08429489/0500'),
('klement', '09584343/0100');

-- --------------------------------------------------------

--
-- Struktura tabulky `studenti_v_kurzech`
--

CREATE TABLE IF NOT EXISTS `studenti_v_kurzech` (
  `uzivatel_nick` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `idkurz` int(5) unsigned zerofill NOT NULL,
  `hodnoceni` enum('1','2','3','4','5') COLLATE utf8_czech_ci DEFAULT NULL,
  PRIMARY KEY (`uzivatel_nick`,`idkurz`),
  KEY `fk_student_has_kurz_kurz1_idx` (`idkurz`),
  KEY `fk_student_has_kurz_student1_idx` (`uzivatel_nick`),
  KEY `hodnoceni` (`hodnoceni`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `studenti_v_kurzech`
--

INSERT INTO `studenti_v_kurzech` (`uzivatel_nick`, `idkurz`, `hodnoceni`) VALUES
('hilsky', 00006, NULL),
('klement', 00006, NULL),
('klement', 00008, NULL),
('lebeda', 00007, NULL),
('novak', 00006, NULL),
('novak', 00007, NULL),
('novak', 00008, NULL),
('packal', 00005, NULL),
('rybnicek', 00005, NULL),
('rybnicek', 00007, NULL),
('rybnicek', 00008, NULL),
('seidlova', 00008, NULL),
('sekyra', 00006, NULL),
('sekyra', 00007, NULL),
('soudkova', 00007, NULL),
('sperk', 00005, NULL),
('sperk', 00007, NULL),
('sperk', 00008, NULL),
('svetly', 00007, NULL),
('svetly', 00008, NULL),
('tluchor', 00005, NULL),
('tluchor', 00008, NULL),
('troufal', 00005, NULL),
('volna', 00007, NULL),
('frejova', 00001, '1'),
('frejova', 00003, '1'),
('lebeda', 00004, '1'),
('packal', 00001, '1'),
('pleva', 00003, '1'),
('tluchor', 00004, '1'),
('frejova', 00002, '2'),
('frejova', 00004, '2'),
('hilsky', 00004, '2'),
('husnik', 00003, '2'),
('klement', 00002, '2'),
('lebeda', 00001, '2'),
('pilna', 00004, '2'),
('pleva', 00004, '2'),
('seidlova', 00002, '2'),
('sekyra', 00001, '2'),
('sekyra', 00003, '2'),
('svetly', 00002, '2'),
('svetly', 00003, '2'),
('hilsky', 00003, '3'),
('novak', 00001, '3'),
('novak', 00002, '3'),
('novak', 00003, '3'),
('packal', 00002, '3'),
('pilna', 00001, '3'),
('pleva', 00001, '3'),
('rybnicek', 00001, '3'),
('sekyra', 00002, '3'),
('sekyra', 00004, '3'),
('vojir', 00001, '3'),
('packal', 00004, '4'),
('pilna', 00002, '4'),
('seidlova', 00001, '4'),
('soudkova', 00002, '4'),
('soudkova', 00003, '4'),
('stalinek', 00002, '4'),
('vojir', 00004, '4'),
('volna', 00001, '4');

-- --------------------------------------------------------

--
-- Struktura tabulky `ucebna`
--

CREATE TABLE IF NOT EXISTS `ucebna` (
  `oznaceni` varchar(5) COLLATE utf8_czech_ci NOT NULL,
  `pocet_mist` int(11) NOT NULL,
  `vybaveni` text COLLATE utf8_czech_ci,
  PRIMARY KEY (`oznaceni`),
  KEY `pocet_mist` (`pocet_mist`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `ucebna`
--

INSERT INTO `ucebna` (`oznaceni`, `pocet_mist`, `vybaveni`) VALUES
('UC01', 10, 'televize, DVD přehrávač'),
('UC02', 15, 'projektor, MP3 přehrávač'),
('UC03', 8, 'počítače, interaktivní tabule, projektor');

-- --------------------------------------------------------

--
-- Struktura tabulky `uzivatel`
--

CREATE TABLE IF NOT EXISTS `uzivatel` (
  `nick` varchar(20) COLLATE utf8_czech_ci NOT NULL,
  `heslo` varchar(128) COLLATE utf8_czech_ci NOT NULL,
  `jmeno` varchar(45) COLLATE utf8_czech_ci DEFAULT NULL,
  `prijmeni` varchar(45) COLLATE utf8_czech_ci NOT NULL,
  `narozeni` date DEFAULT NULL,
  `email` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL,
  `pohlavi` enum('muž','žena') COLLATE utf8_czech_ci DEFAULT NULL,
  `bydliste` varchar(50) COLLATE utf8_czech_ci DEFAULT NULL,
  PRIMARY KEY (`nick`),
  KEY `jmeno` (`prijmeni`,`jmeno`),
  KEY `narozeni` (`narozeni`),
  KEY `pohlavi` (`pohlavi`),
  KEY `bydliste` (`bydliste`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_czech_ci;

--
-- Vypisuji data pro tabulku `uzivatel`
--

INSERT INTO `uzivatel` (`nick`, `heslo`, `jmeno`, `prijmeni`, `narozeni`, `email`, `pohlavi`, `bydliste`) VALUES
('bassova', '82b34e342240a5affc2a92e795ea347d', 'Petra', 'Bassová', '1980-10-06', 'bassova@skola.cz', 'žena', 'Ostrava'),
('coburn', 'bf690cabaffa18c1e940b1cad2779675', 'Peter', 'Coburn', '1977-06-28', 'coburn@school.uk', 'muž', 'Manchester'),
('frejova', '9448caa76c249fbb5bb1b16b57b42e0e', 'Milada', 'Frejová', '1957-08-11', 'frejova@skola.cz', 'žena', 'Brno'),
('grey', '16fe87d4edb6c680d575cbad29c9d9b0', 'Emily', 'Grey', '1993-10-10', 'grey@school.uk', 'žena', 'London'),
('hilsky', 'cb713ac03f05def74fe28b78bb0b6b77', 'Zbyněk', 'Hilský', '1993-07-09', 'hilsky@skola.cz', 'muž', 'Ostrava'),
('hornak', '3d01c6dfedcceeac503eb8e5627ba2b9', 'Martin', 'Horňák', '1991-01-23', 'hornak@skola.cz', 'muž', 'Brno'),
('hruby', '3b1f508a20fd8dba83865d123f53116a', 'Radim', 'Hrubý', '1966-04-21', 'hruby@skola.cz', 'muž', 'Brno'),
('husnik', 'dae1045a54f9d0b929e74b7d9492693a', 'Kamil', 'Husník', '1981-08-12', 'husnik@skola.cz', 'muž', 'Ostrava'),
('klement', '0426e6d80809bb9d3b3b35fb9a00aef3', 'Jiří', 'Klement', '1990-08-23', 'klement@skola.cz', 'muž', 'Opava'),
('lebeda', 'a3090cfe972925a51a48dbec5d95932a', 'Romeo', 'Lebeda', '1995-11-01', 'lebeda@skola.cz', 'muž', 'Ostrava'),
('lopez', '1698bea87b6a501623f30fd9e4efc477', 'Dolores', 'Lopez', '1988-06-17', 'lopez@escuela.sp', 'žena', 'Madrid'),
('novak', '40b8c620c0f6863ea515d35b04b6a4e0', 'Martin', 'Novák', '1993-02-27', 'novak@skola.cz', 'muž', 'Opava'),
('packal', '07c88132d870c14f894c30736c6d10d5', 'Michal', 'Packal', '1990-11-28', 'packal@skola.cz', 'muž', 'Opava'),
('petruskin', '56fcf0c88727358dbff394fe52c49b6a', 'Alexandr', 'Petruškin', '1966-01-04', 'petruskin@skola.ru', 'muž', 'Moskva'),
('pilna', '83a7e5e9916282c72e437474057a2503', 'Marta', 'Pilná', '1992-12-16', 'pilna@skola.cz', 'žena', 'Praha'),
('pleva', '4fe289f4f7bc1fdce33dc83503193b33', 'Jindřich', 'Pleva', '1974-06-14', 'pleva@skola.cz', 'muž', 'Opava'),
('rybnicek', 'e354035e7caab53e898944746a3d69f7', 'Tomáš', 'Rybníček', '1992-07-22', 'rybnicek@skola.cz', 'muž', 'Brno'),
('seidlova', '0542f76723e878a3d7b74f930b5d50aa', 'Mariana', 'Seidlová', '1991-06-08', 'seidlova@skola.cz', 'žena', 'Ostrava'),
('sekyra', 'b29685ef281151a71feb998efbf9713d', 'Dominik', 'Sekyra', '1991-09-21', 'sekyra@skola.cz', 'muž', 'Brno'),
('sobota', 'b86913c5ba05c3cd354b8c2a5552234a', 'Milan', 'Sobota', '1991-11-14', 'sobota@skola.cz', 'muž', 'Ostrava'),
('soudkova', 'f9c693013ff5148e1899c08852f38f06', 'Jana', 'Soudková', '1992-10-14', 'soudkova@skola.cz', 'žena', 'Ostrava'),
('sperk', '2233021d0a470befb6645b673d75e327', 'Jiří', 'Šperk', '1993-10-08', 'sperk@skola.cz', 'muž', 'Brno'),
('stalinek', '58c2198ed413951ab82ddc089fefa5fe', 'Josef', 'Stalinek', '1953-07-16', 'stalinek@skola.cz', 'muž', 'Ostrava'),
('svetly', 'f126ef1e24d71ea52d20315cd89c1382', 'Tomáš', 'Světlý', '1984-12-28', 'svetly@skola.cz', 'muž', 'Ostrava'),
('tluchor', '7e35f200559ca6e5e55ebe8eeba249e7', 'Jiří', 'Tluchoř', '1996-03-15', 'tluchor@skola.cz', 'muž', 'Opava'),
('troufal', 'f630a724ed7a1cd969037af86a20814d', 'Matěj', 'Troufal', '1993-11-13', 'troufal@skola.cz', 'muž', 'Brno'),
('vojir', 'fe00df4f0e2b4f1d8fc42b59cd8f1071', 'Roman', 'Vojíř', '1962-06-17', 'vojir@skola.cz', 'muž', 'Praha'),
('volna', 'e17f25481cfffbc2f5e07e34dc274a93', 'Michaela', 'Volná', '1989-02-11', 'volna@skola.cz', 'žena', 'Olomouc');

--
-- Omezení pro exportované tabulky
--

--
-- Omezení pro tabulku `jazyk_lektoru`
--
ALTER TABLE `jazyk_lektoru`
  ADD CONSTRAINT `fk_lektor_has_jazyk_lektor1` FOREIGN KEY (`lektor`) REFERENCES `lektor` (`uzivatel_nick`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_lektor_has_jazyk_jazyk1` FOREIGN KEY (`jazyk`) REFERENCES `jazyk` (`zkratka`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `kurz`
--
ALTER TABLE `kurz`
  ADD CONSTRAINT `fk_kurz_jazyk1` FOREIGN KEY (`jazyk`) REFERENCES `jazyk` (`zkratka`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_kurz_lektor1` FOREIGN KEY (`lektor`) REFERENCES `lektor` (`uzivatel_nick`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_kurz_ucebna1` FOREIGN KEY (`ucebna_oznaceni`) REFERENCES `ucebna` (`oznaceni`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `lektor`
--
ALTER TABLE `lektor`
  ADD CONSTRAINT `fk_lektor_uzivatel` FOREIGN KEY (`uzivatel_nick`) REFERENCES `uzivatel` (`nick`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `student`
--
ALTER TABLE `student`
  ADD CONSTRAINT `fk_student_uzivatel1` FOREIGN KEY (`uzivatel_nick`) REFERENCES `uzivatel` (`nick`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `studenti_v_kurzech`
--
ALTER TABLE `studenti_v_kurzech`
  ADD CONSTRAINT `fk_student_has_kurz_student1` FOREIGN KEY (`uzivatel_nick`) REFERENCES `student` (`uzivatel_nick`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_student_has_kurz_kurz1` FOREIGN KEY (`idkurz`) REFERENCES `kurz` (`idkurz`) ON DELETE NO ACTION ON UPDATE NO ACTION;
