-- phpMyAdmin SQL Dump
-- version 3.2.2.1deb1
-- http://www.phpmyadmin.net
--
-- Počítač: localhost
-- Vygenerováno: Sobota 03. dubna 2010, 16:27
-- Verze MySQL: 5.1.37
-- Verze PHP: 5.2.10-2ubuntu6.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Databáze: `tj`
--

-- --------------------------------------------------------

--
-- Struktura tabulky `akce`
--

CREATE TABLE IF NOT EXISTS `akce` (
  `id_akce` int(11) NOT NULL,
  `nazev` varchar(50) COLLATE utf8_unicode_ci NOT NULL,
  `datum_konani` date DEFAULT NULL,
  `misto` varchar(30) COLLATE utf8_unicode_ci DEFAULT NULL,
  `typ` enum('sportovní','společenská','kulturní','jiná') COLLATE utf8_unicode_ci DEFAULT 'sportovní',
  `vstupne` decimal(5,2) DEFAULT NULL,
  `pocet_ucastniku` int(6) DEFAULT '0',
  `zprava` text COLLATE utf8_unicode_ci,
  `poradajici_oddil` varchar(5) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id_akce`),
  KEY `fk_zkratka_oddilu` (`poradajici_oddil`),
  KEY `idx_nazev` (`nazev`) USING BTREE,
  KEY `idx_datum` (`datum_konani`) USING BTREE,
  KEY `idx_misto` (`misto`) USING BTREE,
  KEY `idx_ucastnici` (`pocet_ucastniku`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `akce`
--

INSERT INTO `akce` (`id_akce`, `nazev`, `datum_konani`, `misto`, `typ`, `vstupne`, `pocet_ucastniku`, `zprava`, `poradajici_oddil`) VALUES
(1, 'Podzimní turnaj v kopané', '2007-11-17', 'Opava', 'sportovní', '40.00', 1237, 'Turnaje se zúčastnilo 8 týmů z Moravskoslezského kraje. Ve finále porazili vítkovičtí fotbalisté reprezentanty pořádajícího oddílu 4:2.', 'FK'),
(2, 'Boxerská exhibice', '2008-04-16', 'Opava', 'sportovní', '125.00', 342, 'V rámci exhibice mohli přítomní diváci zhlédnout pět utkání. Největší ohlas měl souboj dvou předních českých profesionálních boxerů - Konečného a Matuly.', 'BK'),
(3, 'Volejbalový ples', '2009-01-24', 'Hradec nad Moravicí', 'společenská', '250.00', 231, 'Ples pořádaný opavským volejbalovým klubem se konal v prostorách hradeckého zámku. ', 'VK'),
(4, 'Charitativní sbírka', '2009-03-08', 'Opava', 'jiná', '0.00', 0, 'Atletický klub při TJ Opava uspořádal v rámci oslav MDŽ charitativní sbírku na podporu tělesně postižených sportovců-žen. Bylo vybráno více než 16 tisíc korun. ', 'AK'),
(5, 'Atletická liga', '2009-04-26', 'Opava', 'sportovní', '30.00', 150, 'První kolo druholigového klání atletů se uskutečnilo na Tyršově stadiónu v Opavě. Domácí atleti skončili na druhém místě, atletkám patřila bronzová příčka.', 'AK'),
(6, 'Diskotéka na zimáku', '2009-06-05', 'Opava', 'kulturní', '100.00', 2300, 'Velkou taneční show za účasti několika známých českých DJ uspořádal opavský hokejový klub.', 'HK'),
(7, 'Letní přípravný tábor', '2009-08-10', 'Budišov nad Budišovkou', 'sportovní', '0.00', 30, 'Čtrnáctidenní letní přípravný tábor pro hokejové juniory proběhl v krásném sportovním areálu nedaleko Budišova nad Budišovkou.', 'HK'),
(8, 'Vánoční volejbalový turnaj žen', '2010-12-19', 'Opava', 'sportovní', '40.00', 210, 'Tradičního předvánočního volejbalového turnaje se zúčastnilo 10 ženských týmů. Vítězem se staly volejbalistky z polských Katowic.', 'VK');

-- --------------------------------------------------------

--
-- Struktura tabulky `clenove`
--

CREATE TABLE IF NOT EXISTS `clenove` (
  `oddil_zkratka` varchar(5) COLLATE utf8_unicode_ci NOT NULL,
  `lide_rodne_cislo` varchar(11) COLLATE utf8_unicode_ci NOT NULL,
  `cislo_prukazu` int(4) NOT NULL AUTO_INCREMENT,
  `datum_prijeti` date DEFAULT NULL,
  `funkce` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`cislo_prukazu`,`oddil_zkratka`,`lide_rodne_cislo`),
  KEY `fk_oddil` (`oddil_zkratka`),
  KEY `fk_lide` (`lide_rodne_cislo`),
  KEY `fk_funkce` (`funkce`),
  KEY `idx_prijeti` (`datum_prijeti`) USING BTREE
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=57 ;

--
-- Vypisuji data pro tabulku `clenove`
--

INSERT INTO `clenove` (`oddil_zkratka`, `lide_rodne_cislo`, `cislo_prukazu`, `datum_prijeti`, `funkce`) VALUES
('AK', '720324/7878', 2, '1983-11-13', 'předseda'),
('AK', '900802/4632', 3, '2001-09-28', 'člen'),
('AK', '901222/3346', 4, '2005-05-25', 'pokladník'),
('AK', '911030/6323', 5, '2002-02-01', 'člen'),
('AK', '911206/2074', 6, '2008-03-10', 'člen'),
('AK', '916211/3435', 7, '2002-05-24', 'mluvčí'),
('AK', '920127/7812', 8, '2008-03-26', 'člen'),
('AK', '925412/0678', 9, '2008-11-14', 'člen'),
('AK', '925716/7347', 10, '2006-03-08', 'člen'),
('AK', '926108/7745', 11, '2008-10-06', 'člen'),
('AK', '930218/3120', 12, '2005-11-22', 'člen'),
('AK', '930714/3456', 13, '2011-06-18', 'člen'),
('AK', '930925/3863', 14, '2007-10-20', 'člen'),
('BK', '650512/4325', 17, '1980-06-11', 'místopředseda'),
('BK', '910723/3543', 18, '2003-03-10', 'člen'),
('BK', '810517/5224', 19, '1999-10-09', 'předseda'),
('BK', '750814/4445', 22, '1993-11-23', 'pokladník'),
('BK', '900802/4632', 24, '2008-08-09', 'člen'),
('BK', '720324/7878', 26, '1986-06-23', 'člen'),
('FK', '920403/2189', 32, '2006-07-26', 'člen'),
('FK', '910723/3543', 33, '2008-08-13', 'člen'),
('FK', '920930/7798', 34, '2005-07-14', 'člen'),
('FK', '750814/4445', 35, '1991-07-08', 'předseda'),
('FK', '930821/0442', 36, '2009-09-13', 'člen'),
('FK', '900802/4632', 37, '2008-09-18', 'mluvčí'),
('VK', '930430/1687', 39, '2009-11-11', 'člen'),
('VK', '925412/0678', 40, '2003-05-16', 'člen'),
('VK', '926108/7745', 41, '2006-12-12', 'člen'),
('VK', '930714/3456', 42, '2010-05-08', 'člen'),
('VK', '580913/6432', 43, '1986-09-12', 'předseda'),
('HK', '910723/3543', 46, '2007-05-17', 'člen'),
('HK', '930925/3863', 47, '2009-02-08', 'člen'),
('HK', '926108/7745', 48, '2010-03-23', 'člen'),
('HK', '930819/9785', 49, '2006-10-21', 'člen'),
('HK', '930714/3456', 50, '2004-06-29', 'člen'),
('HK', '911206/2074', 51, '2005-08-24', 'člen'),
('HK', '641103/5433', 52, '1992-03-05', 'předseda'),
('HK', '921226/7846', 53, '2003-04-28', 'člen'),
('HK', '930821/0442', 54, '2010-04-05', 'člen'),
('HK', '911030/6323', 55, '2007-06-23', 'člen'),
('HK', '720324/7878', 56, '1987-08-18', 'člen');

-- --------------------------------------------------------

--
-- Struktura tabulky `funkce`
--

CREATE TABLE IF NOT EXISTS `funkce` (
  `oznaceni` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`oznaceni`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `funkce`
--

INSERT INTO `funkce` (`oznaceni`) VALUES
('člen'),
('kronikář'),
('místopředseda'),
('mluvčí'),
('pokladník'),
('předseda'),
('tajemník');

-- --------------------------------------------------------

--
-- Struktura tabulky `lide`
--

CREATE TABLE IF NOT EXISTS `lide` (
  `rodne_cislo` varchar(11) COLLATE utf8_unicode_ci NOT NULL,
  `prijmeni` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `jmeno` varchar(30) COLLATE utf8_unicode_ci DEFAULT NULL,
  `vyska` int(3) DEFAULT NULL,
  `vaha` int(3) DEFAULT NULL,
  `poznamka` text COLLATE utf8_unicode_ci,
  PRIMARY KEY (`rodne_cislo`),
  KEY `idx_prijmeni` (`prijmeni`) USING BTREE,
  KEY `idx_vyska` (`vyska`) USING BTREE,
  KEY `idx_vaha` (`vaha`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `lide`
--

INSERT INTO `lide` (`rodne_cislo`, `prijmeni`, `jmeno`, `vyska`, `vaha`, `poznamka`) VALUES
('576019/3789', 'Frejová', 'Milada', 158, 78, NULL),
('580913/6432', 'Medřík', 'Milan', 191, 94, NULL),
('641103/5433', 'Kadlec', 'Vojtěch', 179, 85, NULL),
('650512/4325', 'Pleva', 'Jindřich', 174, 75, NULL),
('720324/7878', 'Novák', 'Martin', 198, 82, NULL),
('750814/4445', 'Kalousek', 'Jan', 187, 85, NULL),
('795102/1672', 'Bassová', 'Petra', 161, 57, NULL),
('810517/5224', 'Husník', 'Kamil', 180, 79, NULL),
('900802/4632', 'Klement', 'Jiří', 191, 81, NULL),
('901222/3346', 'Packal', 'Michal', 186, 68, NULL),
('910723/3543', 'Horňák', 'Martin', 176, 78, NULL),
('911030/6323', 'Sobota', 'Milan', 193, 85, NULL),
('911105/3452', 'Sekyra', 'Dominik', 187, 93, NULL),
('911206/2074', 'Tluchoř', 'Jiří', 185, 68, NULL),
('916211/3435', 'Seidlová', 'Mariana', 159, 50, NULL),
('920127/7812', 'Rybníček', 'Tomáš', 174, 63, NULL),
('920403/2189', 'Kouzelník', 'Richard', 175, 70, NULL),
('920930/7798', 'Hrubý', 'Radim', 180, 79, NULL),
('921226/7846', 'Lebeda', 'Romeo', 187, 86, NULL),
('925412/0678', 'Pilná', 'Marta', 171, 48, NULL),
('925716/7347', 'Soudková', 'Jana', 179, 62, NULL),
('926108/7745', 'Rybářová', 'Barbora', 182, 66, NULL),
('930218/3120', 'Troufal', 'Matěj', 203, 93, NULL),
('930430/1687', 'Sekyra', 'Miroslav', 166, 62, NULL),
('930712/7645', 'Vojíř', 'Roman', 183, 81, NULL),
('930714/3456', 'Šperk', 'Jiří', 184, 61, NULL),
('930819/9785', 'Hilský', 'Zbyněk', 182, 83, NULL),
('930821/0442', 'Světlý', 'Tomáš', 187, 92, NULL),
('930925/3863', 'Halámek', 'Michal', 181, 71, NULL);

-- --------------------------------------------------------

--
-- Struktura tabulky `oddily`
--

CREATE TABLE IF NOT EXISTS `oddily` (
  `zkratka` varchar(5) COLLATE utf8_unicode_ci NOT NULL,
  `nazev` varchar(40) COLLATE utf8_unicode_ci NOT NULL,
  `obec` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `ulice` varchar(45) COLLATE utf8_unicode_ci DEFAULT NULL,
  `psc` int(5) DEFAULT NULL,
  `odvetvi` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`zkratka`),
  KEY `idx_nazev` (`nazev`) USING BTREE,
  KEY `idx_obec` (`obec`) USING BTREE,
  KEY `fk_odvetvi` (`odvetvi`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `oddily`
--

INSERT INTO `oddily` (`zkratka`, `nazev`, `obec`, `ulice`, `psc`, `odvetvi`) VALUES
('AK', 'Atletický klub', 'Opava', 'Tyršova 6', 74601, 'atletika'),
('BK', 'Boxerský klub', 'Opava', 'Tyršova 18', 74601, 'box'),
('FK', 'Fotbalový klub', 'Opava', 'Městské sady', 74601, 'fotbal'),
('HK', 'Hokejový klub', 'Opava', 'Zámecký okruh 2', 74601, 'lední hokej'),
('VK', 'Volejbalový klub', 'Opava', 'Mařádkova 41', 74601, 'volejbal');

-- --------------------------------------------------------

--
-- Struktura tabulky `sport_odvetvi`
--

CREATE TABLE IF NOT EXISTS `sport_odvetvi` (
  `sport` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `logo` blob,
  `rok_zalozeni` year(4) DEFAULT NULL,
  PRIMARY KEY (`sport`),
  KEY `idx_zalozeni` (`rok_zalozeni`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `sport_odvetvi`
--

INSERT INTO `sport_odvetvi` (`sport`, `logo`, `rok_zalozeni`) VALUES
('atletika', NULL, 1901),
('box', NULL, 1911),
('fotbal', NULL, 1904),
('lední hokej', NULL, 1902),
('volejbal', NULL, 1937);

--
-- Omezení pro exportované tabulky
--

--
-- Omezení pro tabulku `akce`
--
ALTER TABLE `akce`
  ADD CONSTRAINT `fk_zkratka_oddilu` FOREIGN KEY (`poradajici_oddil`) REFERENCES `oddily` (`zkratka`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `clenove`
--
ALTER TABLE `clenove`
  ADD CONSTRAINT `fk_funkce` FOREIGN KEY (`funkce`) REFERENCES `funkce` (`oznaceni`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_lide` FOREIGN KEY (`lide_rodne_cislo`) REFERENCES `lide` (`rodne_cislo`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_oddil` FOREIGN KEY (`oddil_zkratka`) REFERENCES `oddily` (`zkratka`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `oddily`
--
ALTER TABLE `oddily`
  ADD CONSTRAINT `fk_odvetvi` FOREIGN KEY (`odvetvi`) REFERENCES `sport_odvetvi` (`sport`) ON DELETE NO ACTION ON UPDATE NO ACTION;
