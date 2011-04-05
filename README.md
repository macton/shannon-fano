# Shannon-Fano coding algorithm

	To compile the project:
	
	$ cd shannon-fano
	$ make

	To start the program:

	$ ./shannon-fano

	Shannon-Fano coding archiver
	by Minh Ngo (nlminhtl@gmail.com)

	Ussage: ./shannon-fano OPTION input output
		-p	compressing
		-u	uncompressing
	
## Example

	$ cat makefile

	main:
		gcc main.c bintree.c bitop.c pack.c sort.c unpack.c -o shannon-fano

	$ ./shannon-fano -p makefile dd.sf

	code table size: 23
	c->0000
	 ->0001
	n->001
	a->010
	.->011
	i->10000
	p->10001
	t->1001
	o->1010
	e->10110
	-->10111
	k->110000
	b->110001

	->11001
	r->11010
	m->11011
	s->111000
	g->111001
	h->111010
	:->111011
		->111100
	u->111101
	f->11111
	11011010100000011110111100111110011100100000000000111011010100000010110000000
	11100011000000110011101010110101100110000000111000110000100110101000101100000
	00110001010000011000001100000001111000101011010100101100000001111101001100010
	10000011000001100000001101111010000111100011101001000100110100011011111111010
	001101011001

	$ ./shannon-fano -u dd.sf dd
	$ cat dd

	main:
		gcc main.c bintree.c bitop.c pack.c sort.c unpack.c -o shannon-fano
