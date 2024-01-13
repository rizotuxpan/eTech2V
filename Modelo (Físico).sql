ALTER TABLE `arco` DROP FOREIGN KEY `fk_arco_arcoestructura_1`;
ALTER TABLE `arcocamara` DROP FOREIGN KEY `fk_arcocamara_arco_1`;
ALTER TABLE `arcocamara` DROP FOREIGN KEY `fk_arcocamara_camara_1`;
ALTER TABLE `arcogabinete` DROP FOREIGN KEY `fk_arcogabinete_arco_1`;
ALTER TABLE `arcogabinete` DROP FOREIGN KEY `fk_arcogabinete_gabinete_1`;
ALTER TABLE `arcoradio` DROP FOREIGN KEY `fk_arcoradio_arco_1`;
ALTER TABLE `arcoradio` DROP FOREIGN KEY `fk_arcoradio_radio_1`;
ALTER TABLE `arcoswitch` DROP FOREIGN KEY `fk_arcoswitch_arco_1`;
ALTER TABLE `arcoswitch` DROP FOREIGN KEY `fk_arcoswitch_switch_1`;
ALTER TABLE `camara` DROP FOREIGN KEY `fk_camara_camaramodelo_1`;
ALTER TABLE `camaramodelo` DROP FOREIGN KEY `fk_camaramodelo_camaramodelomarca_1`;
ALTER TABLE `camaramodelo` DROP FOREIGN KEY `fk_camaramodelo_camaramodelotipo_1`;
ALTER TABLE `grupo1` DROP FOREIGN KEY `fk_grupo1_pmi_1`;
ALTER TABLE `grupo2` DROP FOREIGN KEY `fk_grupo2_pmi_1`;
ALTER TABLE `grupo3` DROP FOREIGN KEY `fk_grupo3_pmi_1`;
ALTER TABLE `pmi` DROP FOREIGN KEY `fk_pmi_poste_1`;
ALTER TABLE `pmicamara` DROP FOREIGN KEY `fk_pmicamaras_pmi_1`;
ALTER TABLE `pmicamara` DROP FOREIGN KEY `fk_pmicamara_camara_1`;
ALTER TABLE `pmigabinete` DROP FOREIGN KEY `fk_pmigabinete_pmi_1`;
ALTER TABLE `pmigabinete` DROP FOREIGN KEY `fk_pmigabinete_gabinete_1`;
ALTER TABLE `pmiposte` DROP FOREIGN KEY `fk_poste_postematerial_1`;
ALTER TABLE `pmiradio` DROP FOREIGN KEY `fk_pmiradio_pmi_1`;
ALTER TABLE `pmiradio` DROP FOREIGN KEY `fk_pmiradio_radio_1`;
ALTER TABLE `pmiswitch` DROP FOREIGN KEY `fk_pmiswitch_pmi_1`;
ALTER TABLE `pmiswitch` DROP FOREIGN KEY `fk_pmiswitch_switch_1`;
ALTER TABLE `radio` DROP FOREIGN KEY `fk_radio_radiomodelo_1`;
ALTER TABLE `radiomodelo` DROP FOREIGN KEY `fk_radiomodelo_radiomodelomarca_1`;
ALTER TABLE `switch` DROP FOREIGN KEY `fk_switch_switchmodelo_1`;
ALTER TABLE `switchmodelo` DROP FOREIGN KEY `fk_switchmodelo_switchmodelomarca_1`;
ALTER TABLE `switchmodelo` DROP FOREIGN KEY `fk_switchmodelo_switchmodelotipo_1`;

DROP TABLE IF EXISTS `arco`;
DROP TABLE IF EXISTS `arcocamara`;
DROP TABLE IF EXISTS `arcoestructura`;
DROP TABLE IF EXISTS `arcogabinete`;
DROP TABLE IF EXISTS `arcoradio`;
DROP TABLE IF EXISTS `arcoswitch`;
DROP TABLE IF EXISTS `camara`;
DROP TABLE IF EXISTS `camaramodelo`;
DROP TABLE IF EXISTS `camaramodelomarca`;
DROP TABLE IF EXISTS `camaramodelotipo`;
DROP TABLE IF EXISTS `gabinete`;
DROP TABLE IF EXISTS `grupo1`;
DROP TABLE IF EXISTS `grupo2`;
DROP TABLE IF EXISTS `grupo3`;
DROP TABLE IF EXISTS `nivel4`;
DROP TABLE IF EXISTS `pmi`;
DROP TABLE IF EXISTS `pmicamara`;
DROP TABLE IF EXISTS `pmigabinete`;
DROP TABLE IF EXISTS `pmiposte`;
DROP TABLE IF EXISTS `pmipostematerial`;
DROP TABLE IF EXISTS `pmiradio`;
DROP TABLE IF EXISTS `pmiswitch`;
DROP TABLE IF EXISTS `radio`;
DROP TABLE IF EXISTS `radiomodelo`;
DROP TABLE IF EXISTS `radiomodelomarca`;
DROP TABLE IF EXISTS `switch`;
DROP TABLE IF EXISTS `switchmodelo`;
DROP TABLE IF EXISTS `switchmodelomarca`;
DROP TABLE IF EXISTS `switchmodelotipo`;

CREATE TABLE `arco`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  `lon` varchar(20) NULL,
  `lat` varchar(20) NULL,
  `geom` geometry NULL,
  `gabinete_id` int NULL,
  `estructrura_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `arcocamara`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `arco_id` int NULL,
  `camara_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `arcoestructura`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  `altura` varchar(10) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `arcogabinete`  (
  `id` int NOT NULL,
  `arco_id` int NULL,
  `gabinete_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `arcoradio`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `arco_id` int NULL,
  `radio_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `arcoswitch`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `arco_id` int NULL,
  `switch_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `camara`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `serie` varchar(60) NULL,
  `camaramodelo_id` int NULL,
  `costofactura` decimal(10, 2) UNSIGNED NULL DEFAULT 0.00,
  PRIMARY KEY (`id`)
);

CREATE TABLE `camaramodelo`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  `camaramodelomarca_id` int NULL,
  `camaramodelotipo_id` int NULL,
  PRIMARY KEY (`id` DESC)
);

CREATE TABLE `camaramodelomarca`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `camaramodelotipo`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `gabinete`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `grupo1`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `grupo2`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `grupo3`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `nivel4`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `pmi`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `lon` varchar(20) NULL,
  `lat` varchar(20) NULL,
  `geom` geometry NULL,
  `poste_id` int NULL,
  `grupo1_id` int NULL,
  `grupo2_id` int NULL,
  `grupo3_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `pmicamara`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `pmi_id` int NULL,
  `camara_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `pmigabinete`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `pmi_id` int NULL,
  `gabinete_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `pmiposte`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  `altura` tinyint NULL,
  `postematerial_id` int NOT NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `pmipostematerial`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `pmiradio`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `pmi_id` int NULL,
  `radio_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `pmiswitch`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `pmi_id` int NULL,
  `switch_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `radio`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `serie` varchar(20) NOT NULL,
  `radiomodelo_id` int NULL,
  PRIMARY KEY (`id` DESC)
);

CREATE TABLE `radiomodelo`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  `radiomodelomarca_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `radiomodelomarca`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id` DESC)
);

CREATE TABLE `switch`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `serie` varchar(20) NULL,
  `switchmodelo_id` int NULL,
  `puertos` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `switchmodelo`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NOT NULL,
  `descr` varchar(255) NULL,
  `switchmodelomarca_id` int NULL,
  `switchmodelotipo_id` int NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `switchmodelomarca`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

CREATE TABLE `switchmodelotipo`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `clave` varchar(20) NULL,
  `descr` varchar(255) NULL,
  PRIMARY KEY (`id`)
);

ALTER TABLE `arco` ADD CONSTRAINT `fk_arco_arcoestructura_1` FOREIGN KEY (`estructrura_id`) REFERENCES `arcoestructura` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `arcocamara` ADD CONSTRAINT `fk_arcocamara_arco_1` FOREIGN KEY (`arco_id`) REFERENCES `arco` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `arcocamara` ADD CONSTRAINT `fk_arcocamara_camara_1` FOREIGN KEY (`camara_id`) REFERENCES `camara` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `arcogabinete` ADD CONSTRAINT `fk_arcogabinete_arco_1` FOREIGN KEY (`arco_id`) REFERENCES `arco` (`id`);
ALTER TABLE `arcogabinete` ADD CONSTRAINT `fk_arcogabinete_gabinete_1` FOREIGN KEY (`gabinete_id`) REFERENCES `gabinete` (`id`);
ALTER TABLE `arcoradio` ADD CONSTRAINT `fk_arcoradio_arco_1` FOREIGN KEY (`arco_id`) REFERENCES `arco` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `arcoradio` ADD CONSTRAINT `fk_arcoradio_radio_1` FOREIGN KEY (`radio_id`) REFERENCES `radio` (`id`);
ALTER TABLE `arcoswitch` ADD CONSTRAINT `fk_arcoswitch_arco_1` FOREIGN KEY (`arco_id`) REFERENCES `arco` (`id`);
ALTER TABLE `arcoswitch` ADD CONSTRAINT `fk_arcoswitch_switch_1` FOREIGN KEY (`switch_id`) REFERENCES `switch` (`id`);
ALTER TABLE `camara` ADD CONSTRAINT `fk_camara_camaramodelo_1` FOREIGN KEY (`camaramodelo_id`) REFERENCES `camaramodelo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `camaramodelo` ADD CONSTRAINT `fk_camaramodelo_camaramodelomarca_1` FOREIGN KEY (`camaramodelomarca_id`) REFERENCES `camaramodelomarca` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `camaramodelo` ADD CONSTRAINT `fk_camaramodelo_camaramodelotipo_1` FOREIGN KEY (`camaramodelotipo_id`) REFERENCES `camaramodelotipo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `grupo1` ADD CONSTRAINT `fk_grupo1_pmi_1` FOREIGN KEY (`id`) REFERENCES `pmi` (`grupo1_id`);
ALTER TABLE `grupo2` ADD CONSTRAINT `fk_grupo2_pmi_1` FOREIGN KEY (`id`) REFERENCES `pmi` (`grupo2_id`);
ALTER TABLE `grupo3` ADD CONSTRAINT `fk_grupo3_pmi_1` FOREIGN KEY (`id`) REFERENCES `pmi` (`grupo3_id`);
ALTER TABLE `pmi` ADD CONSTRAINT `fk_pmi_poste_1` FOREIGN KEY (`poste_id`) REFERENCES `pmiposte` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `pmicamara` ADD CONSTRAINT `fk_pmicamaras_pmi_1` FOREIGN KEY (`id`) REFERENCES `pmi` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `pmicamara` ADD CONSTRAINT `fk_pmicamara_camara_1` FOREIGN KEY (`camara_id`) REFERENCES `camara` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `pmigabinete` ADD CONSTRAINT `fk_pmigabinete_pmi_1` FOREIGN KEY (`pmi_id`) REFERENCES `pmi` (`id`);
ALTER TABLE `pmigabinete` ADD CONSTRAINT `fk_pmigabinete_gabinete_1` FOREIGN KEY (`gabinete_id`) REFERENCES `gabinete` (`id`);
ALTER TABLE `pmiposte` ADD CONSTRAINT `fk_poste_postematerial_1` FOREIGN KEY (`postematerial_id`) REFERENCES `pmipostematerial` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `pmiradio` ADD CONSTRAINT `fk_pmiradio_pmi_1` FOREIGN KEY (`pmi_id`) REFERENCES `pmi` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `pmiradio` ADD CONSTRAINT `fk_pmiradio_radio_1` FOREIGN KEY (`radio_id`) REFERENCES `radio` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `pmiswitch` ADD CONSTRAINT `fk_pmiswitch_pmi_1` FOREIGN KEY (`pmi_id`) REFERENCES `pmi` (`id`);
ALTER TABLE `pmiswitch` ADD CONSTRAINT `fk_pmiswitch_switch_1` FOREIGN KEY (`switch_id`) REFERENCES `switch` (`id`);
ALTER TABLE `radio` ADD CONSTRAINT `fk_radio_radiomodelo_1` FOREIGN KEY (`radiomodelo_id`) REFERENCES `radiomodelo` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `radiomodelo` ADD CONSTRAINT `fk_radiomodelo_radiomodelomarca_1` FOREIGN KEY (`radiomodelomarca_id`) REFERENCES `radiomodelomarca` (`id`) ON DELETE CASCADE ON UPDATE CASCADE;
ALTER TABLE `switch` ADD CONSTRAINT `fk_switch_switchmodelo_1` FOREIGN KEY (`switchmodelo_id`) REFERENCES `switchmodelo` (`id`);
ALTER TABLE `switchmodelo` ADD CONSTRAINT `fk_switchmodelo_switchmodelomarca_1` FOREIGN KEY (`switchmodelomarca_id`) REFERENCES `switchmodelomarca` (`id`);
ALTER TABLE `switchmodelo` ADD CONSTRAINT `fk_switchmodelo_switchmodelotipo_1` FOREIGN KEY (`switchmodelotipo_id`) REFERENCES `switchmodelotipo` (`id`);

