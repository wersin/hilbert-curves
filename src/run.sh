#!/bin/sh

hindex_degree=1
file_name="hilbert"

handle_input()
{
    while getopts "d:f:cht" opt; do
        case $opt in
        d)
            hindex_degree=$OPTARG
            ;;
        f)
            file_name=$OPTARG
            ;;
        c)
            use_c=1
            ;;
        t)
            html=1
            ;;
        h)
            print_help=1
            ;;
        \?)
            echo "Invalid option: -$OPTARG" >&2
            exit 1
            ;;
        esac
    done
}

main()
{
    handle_input $@
    make >/dev/null 2>&1

    if [ -z ${print_help+x} ]; then
        a=1
    else
        ./bin/main -h
        exit 1
    fi

    if [ -z ${use_c+x} ]; then
        if [ -z ${html+x} ]; then
            ./bin/main -d $hindex_degree -f ./output/$file_name
        else
            ./bin/main -d $hindex_degree -f ./output/$file_name -t
        fi
    else
        if [ -z ${html+x} ]; then
            ./bin/main -d $hindex_degree -f ./output/$file_name -c
        else
            ./bin/main -d $hindex_degree -f ./output/$file_name -c -t
        fi
    fi
    exit 0
}

main "$@"
