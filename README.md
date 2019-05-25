# MinimumSpanningTree

6 tests :

-boostgraph_test 
-k_clusters_test
-kruskal_test
-prim_test
-boruvka_test
-mipiprimtest


Appel à "make name_test" dans le terminal.
Execution : 

	-Fichier de vecteur : 

	./name_test fichier.txt 
	(fichier.txt = "appendis.txt","auto.txt","bateau.txt","iris.txt" ou dans le fichier "autres donnes"). 
	Par défaut pour : boostgraph_test, k_clusters_test, kruskal_test, prim_test


	-Fichier de edge : 

	./name_test ./data_produced/fichier.txt 
	Par défaut pour : boruvka_test, mipiprimtest


Pour changer de construteur par défaut, il faut passer de : 

boostgraph(std::string file,dist& d) à boostgraph(std::string file)
(fichier de vecteurs ou fichier de edge)
