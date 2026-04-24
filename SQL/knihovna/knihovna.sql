-- phpMyAdmin SQL Dump
-- version 3.2.2.1deb1
-- http://www.phpmyadmin.net
--
-- Počítač: localhost
-- Vygenerováno: Sobota 03. dubna 2010, 10:40
-- Verze MySQL: 5.1.37
-- Verze PHP: 5.2.10-2ubuntu6.4

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Databáze: `knihovna`
--

-- --------------------------------------------------------

--
-- Struktura tabulky `autor`
--

CREATE TABLE IF NOT EXISTS `autor` (
  `id_autora` int(11) NOT NULL AUTO_INCREMENT,
  `prijmeni` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `jmeno` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `zivotopis` text COLLATE utf8_unicode_ci,
  PRIMARY KEY (`id_autora`),
  KEY `idx_prijmeni` (`prijmeni`) USING BTREE
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=7 ;

--
-- Vypisuji data pro tabulku `autor`
--

INSERT INTO `autor` (`id_autora`, `prijmeni`, `jmeno`, `zivotopis`) VALUES
(1, 'Tolstoj', 'Lev Nikolajevič', 'Ruský prozaik, dramatik, publicista, myslitel, filosof a pedagog, všestranná umělecká osobnost světové literatury. Zakladatel křesťanské náboženské koncepce hlásající pasívní rezistenci a nepřetržité mravní sebezdokonalování člověka, přední představitel kritického realismu.'),
(2, 'Camus', 'Albert', 'Francouzský spisovatel a publicista. Bývá uváděn jako jeden z čelných představitelů existencialismu, přestože taková označení odmítal. Stejně tak si nepřál, aby byl pokládán za filosofa, nicméně pozdější filosofické myšlení výrazně ovlivnil.'),
(3, 'Čapek', 'Karel', 'Během svého života vytvořil rozsáhlá díla rozmanitých žánrů a literárních útvarů - od osobitých literárních sloupků přes povídku, cestopis, román až po dramatickou literární tvorbu. V jeho dílech se kromě filozofické podstaty výrazně prosazuje i autorův humanismus, který nebyl jen porozuměním a hlubokým citem pro člověka, nýbrž podstatou Čapkova životního a světového názoru, měřítkem všech otázek, hodnot a jevů, které se stávaly centrem jeho tvůrčího myšlení a literární tvorby.'),
(4, 'Vančura', 'Vladislav', 'Český spisovatel (autor próz s lyrickými prvky i vypravěčských románů), dramatik, filmový scénárista a režisér (např. snímků ''Marijka nevěrnice'', ''Na sluneční straně'', ''Před maturitou''), autor filmových libret a pohádkové knížky. Narodil se v Háji u Opavy, původním povoláním byl lékař. Jeho prozaické dílo, vycházející z experimentálního a expresívního pojetí, se vyznačuje hledáním nových forem, osobitým slohem a jazykem, zejména v typické větné periodě a v lexikálních archaismech. Zahrnuje monumentalizaci chudoby, groteskní apokalypsu, úsměvnou humoresku i jazykový experiment. Ve třicátých letech se obrátil k velkorysé epice, společenskému románu a povídkám. Často používal hyperboly, parodii nebo ironii. Byl synovcem spisovatele Jiřího Mahena a prvním předsedou ''Devětsilu''. Po atentátu na říšského protektora Reinharda Heydricha (1904-1942) byl zatčen gestapem a popraven v koncentračním táboře v Praze-Kobylisích.'),
(5, 'Němcová', 'Božena', 'Příjmení Panklová získala, až když si její matku Terezii Novotnou v létě roku 1820 vzal Johann Pankl. Roku 1821 se Panklovi přestěhovali do Ratibořic, kam se za nimi přistěhovala i její babička – Magdaléna Novotná (1825), která malou Barunku velmi ovlivnila; v dospělosti si babičku velmi zidealizovala.'),
(6, 'King', 'Stephen', 'Stephen King je jeden z nejprodávanějších, nejkultovnějších a nejbohatších žijících spisovatelů, považovaný za bezkonkurenčního mistra moderního hororu a thrilleru. Za třicet let své literární kariéry vydal více než čtyřicet knih, kterých se na celém světě prodalo přes dvě miliardy výtisků. Podle těchto knih bylo natočeny desítky filmů. V jeho fanklubu najdete téměř milión obyvatel této planety...');

-- --------------------------------------------------------

--
-- Struktura tabulky `autori_knih`
--

CREATE TABLE IF NOT EXISTS `autori_knih` (
  `id_autora` int(11) NOT NULL,
  `kniha_isbn` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id_autora`,`kniha_isbn`),
  KEY `fk_autor` (`id_autora`),
  KEY `fk_kniha` (`kniha_isbn`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `autori_knih`
--

INSERT INTO `autori_knih` (`id_autora`, `kniha_isbn`) VALUES
(1, '80-7145-861-9'),
(1, '978-80-7335-123-6'),
(1, '978-80-89278-07-7'),
(2, '978-80-7407-049-5'),
(3, '978-80-200-1678-2'),
(3, '978-80-7335-179-3'),
(4, '80-200-1593-0'),
(4, '80-7217-307-3'),
(5, '80-7360-708-5'),
(6, '80-7306-094-9 '),
(6, '80-85601-26-5');

-- --------------------------------------------------------

--
-- Struktura tabulky `ctenar`
--

CREATE TABLE IF NOT EXISTS `ctenar` (
  `cislo_prukazu` int(5) NOT NULL AUTO_INCREMENT,
  `prijmeni` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `jmeno` varchar(30) COLLATE utf8_unicode_ci NOT NULL,
  `titul` enum('Prof.','Doc.','Dr.','Ing.','Mgr.','Bc.') COLLATE utf8_unicode_ci DEFAULT NULL,
  `narozeni` date DEFAULT NULL,
  `obec` varchar(30) COLLATE utf8_unicode_ci DEFAULT NULL,
  `ulice` varchar(50) COLLATE utf8_unicode_ci DEFAULT NULL,
  `psc` int(5) DEFAULT NULL,
  `telefon` varchar(9) COLLATE utf8_unicode_ci DEFAULT NULL,
  PRIMARY KEY (`cislo_prukazu`),
  KEY `idx_prijmeni` (`prijmeni`) USING BTREE,
  KEY `idx_titul` (`titul`) USING BTREE,
  KEY `idx_narozeni` (`narozeni`) USING BTREE,
  KEY `idx_obec` (`obec`) USING BTREE
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci AUTO_INCREMENT=11 ;

--
-- Vypisuji data pro tabulku `ctenar`
--

INSERT INTO `ctenar` (`cislo_prukazu`, `prijmeni`, `jmeno`, `titul`, `narozeni`, `obec`, `ulice`, `psc`, `telefon`) VALUES
(1, 'Pleva', 'Jindřich', 'Ing.', '1965-05-12', 'Štěpánkovice', 'Horní 112', 74728, '602123456'),
(2, 'Frejová', 'Milada', 'Mgr.', '1954-03-02', 'Hradec nad Moravicí', 'Pod zámkem 13', 74741, '777603216'),
(3, 'Bassová', 'Petra', 'Bc.', '1982-04-25', 'Opava', 'Mařádkova 17', 74601, '723133650'),
(4, 'Husník', 'Kamil', NULL, '1981-05-17', 'Opava', 'Těšínská 45', 74601, '553624021'),
(5, 'Novák', 'Martin', 'Dr.', '1972-03-24', 'Hradec nad Moravicí', 'Opavská 56', 74741, '603443190'),
(6, 'Soudková', 'Jana', NULL, '1982-05-20', 'Háj ve Slezsku', 'Polní 132', 74792, '605643008'),
(7, 'Pilná', 'Marta', NULL, '1990-10-24', 'Opava', 'Hradecká 15', 74601, '777031166'),
(8, 'Sekyra', 'Dominik', NULL, '1991-11-05', 'Opava', 'Hálkova 7', 74601, '607459632'),
(9, 'Seidlová', 'Mariana', 'Bc.', '1979-01-09', 'Opava', 'Nádražní okruh 49', 74601, '602440794'),
(10, 'Šperk', 'Jiří', NULL, '1993-07-14', 'Opava', 'Horní náměstí 21', 74601, '737451090');

-- --------------------------------------------------------

--
-- Struktura tabulky `exemplar`
--

CREATE TABLE IF NOT EXISTS `exemplar` (
  `signatura` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `cena` decimal(6,2) NOT NULL DEFAULT '0.00',
  `isbn` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`signatura`),
  KEY `fk_isbn` (`isbn`),
  KEY `idx_cena` (`cena`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `exemplar`
--

INSERT INTO `exemplar` (`signatura`, `cena`, `isbn`) VALUES
('B-001358', '140.00', '80-200-1593-0'),
('B-002789', '235.00', '80-7145-861-9'),
('B-003207', '243.00', '978-80-89278-07-7'),
('B-004567', '213.00', '80-7217-307-3'),
('B-005609', '175.00', '80-85601-26-5'),
('B-007657', '231.50', '978-80-7335-179-3'),
('B-009804', '340.00', '978-80-7335-123-6'),
('B-010878', '165.00', '80-7360-708-5'),
('B-013056', '267.00', '80-7306-094-9 '),
('B-015221', '92.00', '978-80-7407-049-5'),
('B-023410', '80.00', '978-80-200-1678-2'),
('B-045098', '340.50', '80-7360-708-5');

-- --------------------------------------------------------

--
-- Struktura tabulky `kniha`
--

CREATE TABLE IF NOT EXISTS `kniha` (
  `isbn` varchar(20) COLLATE utf8_unicode_ci NOT NULL,
  `titul` varchar(50) COLLATE utf8_unicode_ci DEFAULT NULL,
  `stran` int(11) DEFAULT NULL,
  `zanr` set('romantický','dobrodružný','sci-fi','historický','humoristický','fantasy','jiný') COLLATE utf8_unicode_ci DEFAULT NULL,
  `id_vydavatelstvi` int(11) NOT NULL,
  PRIMARY KEY (`isbn`),
  KEY `fk_vydavatelstvi` (`id_vydavatelstvi`),
  KEY `idx_titul` (`titul`) USING BTREE,
  KEY `idx_stran` (`stran`) USING BTREE,
  KEY `idx_zanr` (`zanr`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `kniha`
--

INSERT INTO `kniha` (`isbn`, `titul`, `stran`, `zanr`, `id_vydavatelstvi`) VALUES
('80-200-1593-0', 'Markéta Lazarová', 168, 'historický', 2),
('80-7145-861-9', 'Novely o ruské duši', 254, 'jiný', 3),
('80-7217-307-3', 'Rozmarné léto', 145, 'humoristický', 1),
('80-7306-094-9 ', 'Misery', 431, 'fantasy', 2),
('80-7360-708-5', 'Babička', 215, 'romantický', 1),
('80-85601-26-5', 'Carrie', 345, 'fantasy', 2),
('978-80-200-1678-2', 'Krakatit', 251, 'romantický,dobrodružný,sci-fi', 3),
('978-80-7335-123-6', 'Anna Kareninová', 880, 'romantický', 2),
('978-80-7335-179-3', 'Anglické listy', 198, 'jiný', 3),
('978-80-7407-049-5', 'Cizinec', 200, 'jiný', 2),
('978-80-89278-07-7', 'Rozprávky a bájky', 176, 'jiný', 3);

-- --------------------------------------------------------

--
-- Struktura tabulky `vydavatelstvi`
--

CREATE TABLE IF NOT EXISTS `vydavatelstvi` (
  `id_vydavatelstvi` int(11) NOT NULL,
  `nazev` varchar(45) COLLATE utf8_unicode_ci NOT NULL,
  PRIMARY KEY (`id_vydavatelstvi`),
  KEY `idx_nazev_vydavatelstvi` (`nazev`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `vydavatelstvi`
--

INSERT INTO `vydavatelstvi` (`id_vydavatelstvi`, `nazev`) VALUES
(1, 'Albatros'),
(3, 'Levné knihy'),
(2, 'Lidové noviny');

-- --------------------------------------------------------

--
-- Struktura tabulky `vypujcka`
--

CREATE TABLE IF NOT EXISTS `vypujcka` (
  `signatura` varchar(10) COLLATE utf8_unicode_ci NOT NULL,
  `cislo_prukazu` int(5) NOT NULL,
  `datum_pujceni` date NOT NULL,
  `datum_vraceni` date DEFAULT NULL,
  `poplatek` decimal(5,2) DEFAULT NULL,
  PRIMARY KEY (`signatura`,`cislo_prukazu`),
  KEY `fk_exemplar` (`signatura`),
  KEY `fk_ctenar` (`cislo_prukazu`),
  KEY `idx_pujceni` (`datum_pujceni`) USING BTREE,
  KEY `idx_vraceni` (`datum_vraceni`) USING BTREE,
  KEY `poplatek` (`poplatek`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci;

--
-- Vypisuji data pro tabulku `vypujcka`
--

INSERT INTO `vypujcka` (`signatura`, `cislo_prukazu`, `datum_pujceni`, `datum_vraceni`, `poplatek`) VALUES
('B-001358', 2, '2009-12-07', '2010-01-12', '10.00'),
('B-001358', 8, '2010-01-05', '2010-03-10', '30.00'),
('B-002789', 4, '2010-12-06', '2010-02-09', '20.00'),
('B-002789', 5, '2010-02-16', '2010-03-15', '0.00'),
('B-004567', 5, '2010-01-04', '2010-02-03', '0.00'),
('B-004567', 7, '2010-04-12', NULL, '0.00'),
('B-005609', 9, '2009-11-09', '2009-12-17', '10.00'),
('B-005609', 10, '2010-02-23', NULL, '0.00'),
('B-007657', 1, '2009-11-22', '2010-01-11', '20.00'),
('B-007657', 4, '2010-03-02', '2010-04-25', '10.00'),
('B-007657', 6, '2010-01-26', '2010-02-22', '0.00'),
('B-009804', 2, '2010-01-13', '2010-02-09', '0.00'),
('B-009804', 5, '2010-03-15', '2010-04-07', '0.00'),
('B-013056', 7, '2010-02-23', '2010-04-05', '10.00'),
('B-015221', 1, '2010-02-15', '2010-03-30', '10.00'),
('B-015221', 3, '2009-11-09', '2010-01-12', '20.00'),
('B-015221', 9, '2010-04-12', NULL, '0.00'),
('B-023410', 3, '2009-12-22', '2010-01-19', '0.00'),
('B-023410', 4, '2009-11-30', '2009-12-21', '0.00'),
('B-023410', 5, '2010-01-27', '2010-02-23', '0.00'),
('B-023410', 10, '2010-03-29', NULL, '0.00'),
('B-045098', 3, '2010-01-20', '2010-02-25', '10.00'),
('B-045098', 8, '2010-03-03', '2010-04-12', '10.00');

--
-- Omezení pro exportované tabulky
--

--
-- Omezení pro tabulku `autori_knih`
--
ALTER TABLE `autori_knih`
  ADD CONSTRAINT `fk_autor` FOREIGN KEY (`id_autora`) REFERENCES `autor` (`id_autora`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_kniha` FOREIGN KEY (`kniha_isbn`) REFERENCES `kniha` (`isbn`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `exemplar`
--
ALTER TABLE `exemplar`
  ADD CONSTRAINT `fk_isbn` FOREIGN KEY (`isbn`) REFERENCES `kniha` (`isbn`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `kniha`
--
ALTER TABLE `kniha`
  ADD CONSTRAINT `fk_vydavatelstvi` FOREIGN KEY (`id_vydavatelstvi`) REFERENCES `vydavatelstvi` (`id_vydavatelstvi`) ON DELETE NO ACTION ON UPDATE NO ACTION;

--
-- Omezení pro tabulku `vypujcka`
--
ALTER TABLE `vypujcka`
  ADD CONSTRAINT `fk_ctenar` FOREIGN KEY (`cislo_prukazu`) REFERENCES `ctenar` (`cislo_prukazu`) ON DELETE NO ACTION ON UPDATE NO ACTION,
  ADD CONSTRAINT `fk_exemplar` FOREIGN KEY (`signatura`) REFERENCES `exemplar` (`signatura`) ON DELETE NO ACTION ON UPDATE NO ACTION;
