DROP TABLE astros.Equip_avist;
DROP TABLE astros.Avist_astro;
DROP TABLE astros.Astro;
DROP TABLE astros.Sistema_solar;
DROP TABLE astros.Imagem;
DROP TABLE astros.Avistamento;
DROP TABLE astros.Local;
DROP TABLE astros.Publicacao;
DROP TABLE astros.Equipamento;
DROP TABLE astros.Tipo_equipamento;
DROP TABLE astros.Usuario;
DROP SCHEMA astros;

CREATE SCHEMA astros AUTHORIZATION postgres;

/* Modelo Logico: */

CREATE TABLE astros.Usuario (
    id_usuario serial PRIMARY KEY,
    nome_usuario varchar(50),
    email_usuario varchar(50),
    bio_usuario varchar(200),
    data_nasc_usu date,
    pword_usuario varchar
);

CREATE TABLE astros.Publicacao (
    id_publi serial PRIMARY KEY,
    desc_publi varchar(1000),
    data_publi timestamp,
    is_public boolean
);

CREATE TABLE astros.Astro (
    id_astro serial PRIMARY KEY,
    nome_astro varchar(50),
    dec_astro varchar(10),
    ra_astro varchar(10),
    distance_astro numeric,
    excen_cometa numeric,
    periodo_cometa integer,
    perielio_cometa numeric,
    afelio_cometa numeric,
    tipo_estrela varchar(30),
    massa_estrela numeric,
    raio_estrela integer,
    mag_apa_estrela numeric,
    mag_abs_estrela numeric,
    tamanho_planeta numeric,
    exoplaneta boolean,
    pos_planeta integer,
    materiais_planeta varchar(100),
    Astro_TIPO INT,
    id_sissolar integer
);

CREATE TABLE astros.Imagem (
    id_imagem serial PRIMARY KEY,
    desc_imagem varchar(100),
    tamanho_imagem numeric,
    id_avistamento integer
);

CREATE TABLE astros.Avistamento (
    id_avistamento serial PRIMARY KEY,
    id_usuario integer,
    id_local integer,
    id_publi integer,
	data_avist timestamp
);

CREATE TABLE astros.Local (
    id_local serial PRIMARY KEY,
    cidade varchar(50),
    estado_prov varchar(50),
    pais varchar(50),
    latitude varchar(20),
    longitude varchar(20),
    UNIQUE (latitude, longitude)
);

CREATE TABLE astros.Equipamento (
    id_equip serial PRIMARY KEY,
    nome_equip varchar(50),
    marca_equip varchar(50),
    espec_equip varchar(500),
    id_tipo_equip integer
);

CREATE TABLE astros.Tipo_Equipamento (
    id_tipo_equip serial PRIMARY KEY,
    desc_tipo_equip varchar(50)
);

CREATE TABLE astros.Sistema_Solar (
    id_sissolar serial PRIMARY KEY,
    nome_sissolar varchar(50)
);

CREATE TABLE astros.Avist_astro (
    id_astro integer,
    id_avistamento integer
);

CREATE TABLE astros.Equip_avist (
    id_equip integer,
    id_avistamento integer
);
 
ALTER TABLE astros.Astro ADD CONSTRAINT FK_Astro_2
    FOREIGN KEY (id_sissolar)
    REFERENCES astros.Sistema_Solar (id_sissolar)
    ON DELETE SET NULL;
 
ALTER TABLE astros.Imagem ADD CONSTRAINT FK_Imagem_2
    FOREIGN KEY (id_avistamento)
    REFERENCES astros.Avistamento (id_avistamento)
    ON DELETE CASCADE;
 
ALTER TABLE astros.Avistamento ADD CONSTRAINT FK_Avistamento_2
    FOREIGN KEY (id_usuario)
    REFERENCES astros.Usuario (id_usuario)
    ON DELETE CASCADE;
 
ALTER TABLE astros.Avistamento ADD CONSTRAINT FK_Avistamento_3
    FOREIGN KEY (id_local)
    REFERENCES astros.Local (id_local)
    ON DELETE CASCADE;
 
ALTER TABLE astros.Avistamento ADD CONSTRAINT FK_Avistamento_4
    FOREIGN KEY (id_publi)
    REFERENCES astros.Publicacao (id_publi)
    ON DELETE SET NULL;
 
ALTER TABLE astros.Equipamento ADD CONSTRAINT FK_Equipamento_2
    FOREIGN KEY (id_tipo_equip)
    REFERENCES astros.Tipo_Equipamento (id_tipo_equip)
    ON DELETE CASCADE;
 
ALTER TABLE astros.Avist_astro ADD CONSTRAINT FK_Avist_astro_1
    FOREIGN KEY (id_astro)
    REFERENCES astros.Astro (id_astro)
    ON DELETE RESTRICT;
 
ALTER TABLE astros.Avist_astro ADD CONSTRAINT FK_Avist_astro_2
    FOREIGN KEY (id_avistamento)
    REFERENCES astros.Avistamento (id_avistamento)
    ON DELETE SET NULL;
 
ALTER TABLE astros.Equip_avist ADD CONSTRAINT FK_Equip_avist_1
    FOREIGN KEY (id_equip)
    REFERENCES astros.Equipamento (id_equip)
    ON DELETE RESTRICT;
 
ALTER TABLE astros.Equip_avist ADD CONSTRAINT FK_Equip_avist_2
    FOREIGN KEY (id_avistamento)
    REFERENCES astros.Avistamento (id_avistamento)
    ON DELETE SET NULL;
	
INSERT INTO astros.Tipo_equipamento (desc_tipo_equip) VALUES ('Binóculos');
INSERT INTO astros.Tipo_equipamento (desc_tipo_equip) VALUES ('Telescópio refrator');
INSERT INTO astros.Tipo_equipamento (desc_tipo_equip) VALUES ('Telescópio refletor');
INSERT INTO astros.Tipo_equipamento (desc_tipo_equip) VALUES ('Telescópio catadiotrópico');
INSERT INTO astros.Tipo_equipamento (desc_tipo_equip) VALUES ('Radiotelescópio');
INSERT INTO astros.Tipo_equipamento (desc_tipo_equip) VALUES ('Telescópio espacial');

INSERT INTO astros.Usuario (nome_usuario, email_usuario, bio_usuario, data_nasc_usu, pword_usuario)
VALUES ('José Norberto', 'norbertojose007@gmail.com', 'Criador da rede social de astros', '2000-05-22', 'jose22');
INSERT INTO astros.Usuario (nome_usuario, email_usuario, bio_usuario, data_nasc_usu, pword_usuario)
VALUES ('Administrador', 'admin@teste.com', 'Usuario administrador', '2023-06-29', 'admin123');
INSERT INTO astros.Usuario (nome_usuario, email_usuario, bio_usuario, data_nasc_usu, pword_usuario)
VALUES ('José Norberto Fagundes Isaias', 'j.norberto@ufsc.br', 'Conta universitária do criador deste rede social', '2000-05-22', 'joseufsc');

INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('Araranguá', 'Santa Catarina', 'Brasil', '-28.943000', '-49.472389');
INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('Arroio do Silva', 'Santa Catarina', 'Brasil', '-29.025168', '-49.451889');
INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('Sombrio', 'Santa Catarina', 'Brasil', '-29.102017', '-49.638423');
INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('São Paulo', 'São Paulo', 'Brasil', '-23.557210', '-46.685456');
INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('Rio de Janeiro', 'Rio de Janeiro', 'Brasil', '-22.951895', '-43.211337');
INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('Santa Cruz de Tenerife', 'Ilhas Canárias', 'Espanha', '28.752373', '-17.890823');
INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('San Pedro de Atacama', 'Antofagasta', 'Chile', '-23.037572', '-67.735854');
INSERT INTO astros.Local (cidade, estado_prov, pais, latitude, longitude)
VALUES ('Qiannan Buyei and Miao Autonomous Prefecture', 'Guizhou', 'China', '25.652779', '106.856622');

INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('Hubble', 'NASA', 'Opera a uma altitude de 560 km da superfície
Espelho principal de 2,4 metros de diâmetro
Capaz de captar raios gama, raios-X e infravermelho', 5);
INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('Fermi', 'NASA', 'Detecta raios Gama
Conta com um LAT (Telescópio de grande área)
Conta com GBM (Explosão de raios gama)
LAT com quatro susbsistemas para filtrar a energia dos raios gama.', 6);
INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('Chandra', 'NASA', 'Detecta raios-X
Conta com quatro espelhos mais resistentes
Usa espectômetros LETG e HETG
Capaz de observar Supernovas e seus remanescentes.', 6);
INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('Gran Telescopio Canarias', 'Instituto de Astrofísica de Canarias', 'Espelho refletor de 10.4m segmentado em 36 peças hexagonais
Controlado pele sistema ativo-ótico
Poder de visão e luminosidade de 4 milhões de pupilas humanas.', 5);
INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('SOFIA', 'NASA', 'Telescópio refletor de 2.7m de diâmetro
Usa luz infravermelha para observação do espaço
É usado acoplado a um Boeing 747.', 6);
INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('Greika BT400-80EQ', 'Barsta', 'Distância focal de 400mm
Lente objetiva de 80mm
Ampliação de até 220x
Conta com mira laser.', 3);
INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('Travel Scope 70', 'Celestron', 'Distância focal de 400mm
Lente objetiva de 70mm
Ampliação de até 165x
Compatível com Starry Night Software.', 2);
INSERT INTO astros.Equipamento (nome_equip, marca_equip, espec_equip, id_tipo_equip)
VALUES ('Cometron', 'Celestron', 'Distância focal de 400mm
Lente objetiva de 50mm
Ampliação de até 7x
Diâmetro ocular de 25mm.', 1);

INSERT INTO astros.Sistema_solar (nome_sissolar) VALUES('Sistema Sol');

INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Mercúrio', '61 45 00', '18 44 2', NULL, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   2439.7, true, 2, '31.7% potássio, 24.9% sódio, 9,5% oxigênio atômico, 7% argônio e outros',
	   2, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Vênus', '67 16 00', '18 11 2', NULL, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   6051.8, true, 1, '96.5% dióxido de carbono, 3.5% de nitrogênio e outros',
	   2, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Marte', '52 88 50', '21 10 44', NULL, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   3389.5, true, 4, '95.97% dióxido de carbono, 1.93% argônio, 1.89% de nitrogênio e outros',
	   2, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Júpiter', '64 4 95', '17 52 14', NULL, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   69911, true, 5, '89% hidrogênio, 10% hélio, 0.3% metano e outros',
	   2, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Saturno', '83 5 37', '2 42 21', NULL, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   58232, true, 6, '96.3% hidrogênio, 3.25% hélio, 0.45% metano e outros',
	   2, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Urano', '-15 1 75', '17 9 15', NULL, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   25362, true, 7, '83% hidrogênio, 15% hélio, 2.3% metano e outros',
	   2, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Netuno', '42 9 5', '19 57 20', NULL, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   24622, true, 8, '80% hidrogênio, 19% hélio, 1.5% metano e outros',
	   2, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Sol', '63 52 0', '19 4 30', 1, 
	   NULL, NULL, NULL, NULL,
	   'Anã amarela', 1, 695700, -26.74, 4.83,
	   NULL, NULL, NULL, NULL,
	   3, 1);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Upsilon Andromedae A', '41 24 19', '1 36 47', 44, 
	   NULL, NULL, NULL, NULL,
	   'Binária (Anã branca/vermelha)', 1.27, 1.480, 4.63, 3.44,
	   NULL, NULL, NULL, NULL,
	   3, NULL);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Upsilon Andromedae b', '41 24 19', '1 36 47', 43.97, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   128685.6, true, 1, 'Provavelmente Vanádio, Óxido de titânio',
	   2, NULL);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Upsilon Andromedae c', '41 24 19', '1 36 47', 43.97, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   999318.36, true, 2, '',
	   2, NULL);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Upsilon Andromedae d', '41 24 19', '1 36 47', 43.97, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   72911.64, true, 3, '',
	   2, NULL);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Upsilon Andromedae e', '41 24 19', '1 36 47', 43.97, 
	   NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL, NULL,
	   72534.1, true, 4, '',
	   2, NULL);
INSERT INTO astros.Astro (nome_astro, dec_astro, ra_astro, distance_astro,
							  excen_cometa, periodo_cometa, perielio_cometa, afelio_cometa,
							  tipo_estrela, massa_estrela, raio_estrela, mag_apa_estrela, mag_abs_estrela,
							  tamanho_planeta, exoplaneta, pos_planeta, materiais_planeta,
							  Astro_TIPO, id_sissolar)
VALUES ('Cometa Halley', '161 96 0', '59 3 96', NULL, 
	   0.96658, 74.7, 0.59278, 35.14,
	   NULL, NULL, NULL, NULL, NULL,
	   NULL, NULL, NULL, NULL,
	   1, 1);
	   
INSERT INTO astros.Publicacao (desc_publi, data_publi, is_public)
VALUES ('Muito legal isso', '2023-05-22 22:31', true);
INSERT INTO astros.Publicacao (desc_publi, data_publi, is_public)
VALUES ('Quero ver isso de novo', '2023-05-29 12:11', true);
INSERT INTO astros.Publicacao (desc_publi, data_publi, is_public)
VALUES ('Experimentando essa rede social', '2023-06-11 21:21', true);
INSERT INTO astros.Publicacao (desc_publi, data_publi, is_public)
VALUES ('Fazendo mais um post aqui', '2023-06-19 11:11', true);
INSERT INTO astros.Publicacao (desc_publi, data_publi, is_public)
VALUES ('Todo mundo pode ver isso?', '2023-06-22 23:41', true);
INSERT INTO astros.Publicacao (desc_publi, data_publi, is_public)
VALUES ('Viagem legal que fiz para as Ilhas Canárias', '2023-06-29 11:39', true);

INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (1, 1, 1, '2023-05-01 01:23');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (1, 1, 1, '2023-05-03 11:15');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (1, 2, 1, '2023-05-06 02:45');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (1, 3, 2, '2023-05-09 09:22');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (1, 3, 2, '2023-05-10 21:22');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (2, 2, 3, '2023-05-16 23:00');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (2, 2, 3, '2023-05-22 01:11');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (3, 2, 4, '2023-05-26 03:13');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (3, 2, 4, '2023-06-05 18:45');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (3, 4, 4, '2023-06-06 01:30');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (3, 5, 5, '2023-06-10 19:56');
INSERT INTO astros.Avistamento (id_usuario, id_local, id_publi, data_avist) VALUES (1, 6, 6, '2023-06-26 23:45');

INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (8, 1);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (7, 2);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (7, 3);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (6, 3);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (6, 4);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (6, 4);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (7, 5);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (7, 6);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (8, 7);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (5, 8);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (6, 9);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (8, 10);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (7, 10);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (8, 11);
INSERT INTO astros.Equip_avist (id_equip, id_avistamento) VALUES (4, 12);

INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (1, 1);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (2, 1);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (3, 1);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (4, 2);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (5, 2);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (5, 3);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (6, 3);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (6, 4);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (7, 4);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (8, 5);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (1, 5);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (3, 6);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (1, 6);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (4, 7);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (5, 8);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (7, 9);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (4, 9);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (3, 10);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (4, 10);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (7, 11);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (8, 11);
INSERT INTO astros.Avist_astro (id_astro, id_avistamento) VALUES (9, 12);

INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 50, 1);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 13, 2);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 67, 3);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 25.7, 3);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 35, 4);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 63.7, 5);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 89.6, 6);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 50, 6);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 220, 7);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 56, 8);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 50, 9);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 51, 10);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 99.5, 12);
INSERT INTO astros.Imagem (desc_imagem, tamanho_imagem, id_avistamento)
VALUES ('Avistamento no dia dd/MM/yyyy', 50, 12);

